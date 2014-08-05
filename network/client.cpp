#include "client.h"
#include <QHostAddress>
#include <settings.h>
#include "maumauprotokoll.h"

MauClient::MauClient(QObject* parent)
    : QObject(parent)
{
}

void MauClient::setupConnection(QString _address, QString _port)
{
    QHostAddress address = QHostAddress(_address);
    qint16 port = _port.toInt();

    server->connectToHost(address, port);

    //connect(client, SIGNAL(connected()), this, SLOT(write()));
    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError()));
    connect(server, &QTcpSocket::readyRead, this, &MauClient::readNextData);
    //connect(&client, SIGNAL(readyRead()), this, SLOT(read()));
}

void MauClient::OnError()
{
    qDebug() << "socket error";
    if (server->error()) {
        qCritical() << server->error();
        qCritical() << server->errorString();
        qCritical() << server->state();
    }
}

void MauClient::UIplaysCard(const Card& card)
{
    QString message;
    message.append(MProtocol::PLAY_CARD);
    message.append(";");
    message.append(MProtocol::cardToSting(card));
    writeNextData(message);
}

void MauClient::UIdrawsCard()
{
    QString message;
    message.append(MProtocol::DRAW_CARD);
    writeNextData(message);
}
void MauClient::readNextData()
{
    char buf[1024] = { 0 };
    qint64 lineLength = server->readLine(buf, sizeof(buf));
    if (lineLength != -1) {
        handleMessage(QString(buf));
    }
}

void MauClient::writeNextData(QString data)
{
    qDebug() << "send Data: " << data;
    data.append("\n");
    qint64 writtenByteCount = server->write(data.toStdString().c_str());
    if (writtenByteCount == -1 || writtenByteCount < qstrlen(data.toStdString().c_str())) {
        //TODO handle network fail
        qDebug() << "client -> server write failed";
    }
}

void MauClient::handleMessage(QString message)
{
    qDebug() << "recived Data: " << message;
    QStringList messageSplit = message.split(";");
    switch (messageSplit.at(0).toInt()) {
    case MProtocol::INIT_PLAYGROUND:
        emit clientGameStarted();
        playerName = PLAYER::Name(messageSplit.at(1).toInt());
        qDebug() << "client: local/remote Player Name: " << playerName;
        //        void UIinitPlayground(const std::vector<Card> & humanPlayerCards,
        //                              std::map<PLAYER::Name, int> otherPlayerCardCount,
        //                              const Card & topDepotCard,
        //                              PLAYER::Name startingPlayer);
        emit UIinitPlayground(MProtocol::stringToCardVec(messageSplit.at(2)),
                              rotatePlayerMap(MProtocol::stingToCardCountMap(messageSplit.at(3))),
                              MProtocol::stingToCard(messageSplit.at(4)),
                              getLocalPlayerName(PLAYER::Name(messageSplit.at(5).toInt())));

        break;
    case MProtocol::DO_TURN:
        //        void UIdoTurn(std::vector<Card> playableCards,
        //                      Card::cardSuit wishSuitCard);
        emit UIdoTurn(MProtocol::stringToCardVec(messageSplit.at(1)),
                      Card::cardSuit(messageSplit.at(2).toInt()));
        break;
    case MProtocol::OTHER_PLAYS_CARD:
        //        void UIplayerPlaysCard(PLAYER::Name pName,
        //                               const Card & playedCard);
        emit UIplayerPlaysCard(getLocalPlayerName(PLAYER::Name(messageSplit.at(1).toInt())),
                               MProtocol::stingToCard(messageSplit.at(2)));
        break;
    case MProtocol::OTHER_DRAWS_CARD:
        //        void UIplayerDrawsCard(PLAYER::Name pName);
        emit UIplayerDrawsCard(getLocalPlayerName(PLAYER::Name(messageSplit.at(1).toInt())));
        break;
    case MProtocol::ADD_CARD:
        //        void UIaddPlayerCard(const Card & card);
        emit UIaddPlayerCard(MProtocol::stingToCard(messageSplit.at(1)));
        break;
    default:
        qDebug() << "method not found";
        break;
    }
}

std::map<PLAYER::Name, int> MauClient::rotatePlayerMap(std::map<PLAYER::Name, int> otherPlayerCardCount)
{
    std::map<PLAYER::Name, int> rotatedMap;
    rotatedMap.insert(std::pair<PLAYER::Name, int>(getLocalPlayerName(PLAYER::BOTTOM), otherPlayerCardCount.at(PLAYER::BOTTOM)));
    rotatedMap.insert(std::pair<PLAYER::Name, int>(getLocalPlayerName(PLAYER::TOP), otherPlayerCardCount.at(PLAYER::TOP)));
    rotatedMap.insert(std::pair<PLAYER::Name, int>(getLocalPlayerName(PLAYER::LEFT), otherPlayerCardCount.at(PLAYER::LEFT)));
    rotatedMap.insert(std::pair<PLAYER::Name, int>(getLocalPlayerName(PLAYER::RIGHT), otherPlayerCardCount.at(PLAYER::RIGHT)));
    return rotatedMap;
}

/**
 * @brief Rotates the player names, so the local player is always on bottom.
 * @param pName the name to be rotated according to the local player position
 * @return
 */
PLAYER::Name MauClient::getLocalPlayerName(PLAYER::Name pName)
{
    int backwardsRotations = playerName;

    for (int i = 0; i < backwardsRotations; ++i) {
        switch (pName) {
        case PLAYER::BOTTOM:
            pName = PLAYER::RIGHT;
            break;
        case PLAYER::LEFT:
            pName = PLAYER::BOTTOM;
            break;
        case PLAYER::TOP:
            pName = PLAYER::LEFT;
            break;
        case PLAYER::RIGHT:
            pName = PLAYER::TOP;
            break;
        }
    }
    return pName;
}

MauClient::~MauClient()
{
    server->close();
}
