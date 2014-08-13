#include "client.h"
#include <QHostAddress>
#include <settings.h>
#include "maumauprotokoll.h"
#include <QMap>
#include <algorithm>
#include <settings.h>

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

void MauClient::UIplaysCard(const Card& card, Card::cardSuit wishedSuit)
{
    QString message;
    message.append(QString::number(MProtocol::PLAY_CARD));
    message.append(";");
    message.append(MProtocol::cardToSting(card));
    message.append(";");
    message.append(QString::number(wishedSuit));
    writeNextData(message);
}

void MauClient::UIdrawsCard()
{
    QString message;
    message.append(QString::number(MProtocol::DRAW_CARD));
    writeNextData(message);
}

void MauClient::writeNextData(QString data)
{
    qDebug() << "send Data: " << data;
    data.append("\n");
    qint64 writtenByteCount = server->write(data.toStdString().c_str());
    if (writtenByteCount == -1 || writtenByteCount < qstrlen(data.toStdString().c_str())) {

        qDebug() << "client -> server write failed";
    }
}

void MauClient::readNextData()
{
    int availableBytes = server->bytesAvailable();
    while (availableBytes > 0) {
        char buff[1024] = { 0 };
        qint64 lineLength = server->readLine(buff, sizeof(buff));
        if (lineLength > 0) {
            handleMessage(QString(buff));
        } else {
            qDebug() << "message length error occured";
        }
        availableBytes = server->bytesAvailable();
    }
}

void MauClient::handleMessage(QString message)
{

    message = message.trimmed();
    qDebug() << "recived Data: " << message;
    QStringList messageSplit = message.split(";");
    qDebug() << "message split size: " << messageSplit.size();

    switch (messageSplit.at(0).toInt()) {
    case MProtocol::INIT_PLAYGROUND: {
        if (messageSplit.size() < 6) {
            qDebug() << "message split error at: " << MProtocol::INIT_PLAYGROUND;
        }
        emit clientGameStarted();
        playerName = PLAYER::Name(messageSplit.at(1).toInt());
        qDebug() << "client: local/remote Player Name: " << playerName;

        std::map<PLAYER::Name, int> otherPlayerCardCount = MProtocol::stingToCardCountMap(messageSplit.at(3));
        for (unsigned i = 0; i < otherPlayerCardCount.size(); ++i) {
            localPlayerOrder.append(PLAYER::Name(i));
        }
        rotatePlayerMap();

        //        void UIinitPlayground(const std::vector<Card> & remotePlayerCards,
        //                              std::map<PLAYER::Name, int> otherPlayerCardCount,
        //                              const Card & topDepotCard,
        //                              Card::cardValue _wishSuitCard);

        emit UIinitPlayground(MProtocol::stringToCardVec(messageSplit.at(2)),
                              otherPlayerCardCount,
                              MProtocol::stingToCard(messageSplit.at(4)),
                              Card::cardValue(messageSplit.at(5).toInt()),
                              MProtocol::stringToStringVec(messageSplit.at(6)));

        break;
    }
    case MProtocol::DO_TURN:
        if (messageSplit.size() < 3) {
            qDebug() << "message split error at: " << MProtocol::DO_TURN;
        }
        //        void UIdoTurn(std::vector<Card> playableCards,
        //                      Card::cardSuit wishedSuit);
        emit UIdoTurn(MProtocol::stringToCardVec(messageSplit.at(1)),
                      Card::cardSuit(messageSplit.at(2).toInt()));
        break;

    case MProtocol::OTHER_PLAYS_CARD:
        if (messageSplit.size() < 3) {
            qDebug() << "message split error at: " << MProtocol::OTHER_PLAYS_CARD;
        }
        //        void UIplayerPlaysCard(PLAYER::Name pName,
        //                               const Card & playedCard);
        emit UIplayerPlaysCard(localPlayerOrder[messageSplit.at(1).toInt()],
                               MProtocol::stingToCard(messageSplit.at(2)));
        break;
    case MProtocol::OTHER_DRAWS_CARD:
        if (messageSplit.size() < 2) {
            qDebug() << "message split error at: " << MProtocol::OTHER_DRAWS_CARD;
        }
        //        void UIplayerDrawsCard(PLAYER::Name pName);
        emit UIplayerDrawsCard(localPlayerOrder[messageSplit.at(1).toInt()]);
        break;
    case MProtocol::ADD_CARD:
        if (messageSplit.size() < 2) {
            qDebug() << "message split error at: " << MProtocol::ADD_CARD;
        }
        //        void UIaddPlayerCard(const Card & card);
        emit UIaddPlayerCard(MProtocol::stingToCard(messageSplit.at(1)));
        break;
    case MProtocol::PLAYER_WON:
        if (messageSplit.size() < 2) {
            qDebug() << "message split error at: " << MProtocol::ADD_CARD;
        }
        qDebug() << "Player " << messageSplit.at(1) << " won, signal to view not implemented yet";
        break;
    case MProtocol::REQUEST_NAME: {
        QString message;
        QString playerName = Settings::getInstance()->getProperty("common/playername");
        message.append(QString::number(MProtocol::SEND_NAME));
        message.append(";");
        message.append(QString::number(messageSplit.at(1).toInt()));
        message.append(";");
        message.append(playerName);
        writeNextData(message);
        break;
    }
    case MProtocol::CONNECTION_REJECTED:
        emit connectionRejected();
        break;
    case MProtocol::CONNECTION_ACCEPTED:
        emit connectionAccepted();
        break;
    default:
        qDebug() << "method not found";
        break;
    }
}

void MauClient::rotatePlayerMap()
{
    std::rotate(localPlayerOrder.begin(), localPlayerOrder.begin() + playerName, localPlayerOrder.end());
}

//std::map<PLAYER::Name, int> MauClient::rotatePlayerMap(std::map<PLAYER::Name, int> otherPlayerCardCount)
//{

//    std::map<PLAYER::Name, int> rotatedMap = otherPlayerCardCount;
//    std::rotate(rotatedMap.begin(), rotatedMap.begin() + static_cast<int>(playerName), rotatedMap.end());
//    localPlayerOrder = QMap<PLAYER::Name, int>(rotatedMap).keys();
//    return rotatedMap;
//}

///**
// * @brief Rotates the player names, so the local player is always on bottom.
// * @param pName the name to be rotated according to the local player position
// * @return
// */
//PLAYER::Name MauClient::getLocalPlayerName(PLAYER::Name pName)
//{
//    int backwardsRotations = playerName;

//    for (int i = 0; i < backwardsRotations; ++i) {
//        switch (pName) {
//        case PLAYER::BOTTOM:
//            pName = PLAYER::RIGHT;
//            break;
//        case PLAYER::LEFT:
//            pName = PLAYER::BOTTOM;
//            break;
//        case PLAYER::TOP:
//            pName = PLAYER::LEFT;
//            break;
//        case PLAYER::RIGHT:
//            pName = PLAYER::TOP;
//            break;
//        }
//    }
//    return pName;
//}

MauClient::~MauClient()
{
    server->close();
}
