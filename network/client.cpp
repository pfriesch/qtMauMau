#include "client.h"
#include <QHostAddress>
#include <settings.h>
#include "maumauprotokoll.h"
#include <QMap>
#include <algorithm>
#include <settings.h>

/**
 * @brief MauClient::MauClient
 * @param parent
 */
MauClient::MauClient(QObject* parent)
    : QObject(parent)
{
}
/**
 * Connects readyread and error signals woth the corresponding slots in this class
 * @brief MauClient::setupConnection sets up the connection with the given address and port
 * @param _address the address to connect to
 * @param _port the port of the connection
 */
void MauClient::setupConnection(QString _address, QString _port)
{
    QHostAddress address = QHostAddress(_address);
    qint16 port = _port.toInt();

    server->connectToHost(address, port);

    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError()));
    connect(server, &QTcpSocket::readyRead, this, &MauClient::readNextData);
}
/**
 * @brief MauClient::OnError slot handles errors of the connection
 */
void MauClient::OnError()
{
    if (server->error()) {
        qCritical() << server->error();
        qCritical() << server->errorString();
        qCritical() << server->state();
    }
}
/**
 * @brief MauClient::UIplaysCard constructs a MProtocol message of the slot type and sends it
 * @param card the card the player played
 * @param wishedSuit the wished suit
 */
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
/**
 * @brief MauClient::UIdrawsCard constructs a MProtocol message of the slot type and sends it
 */
void MauClient::UIdrawsCard()
{
    QString message;
    message.append(QString::number(MProtocol::DRAW_CARD));
    writeNextData(message);
}
/**
 * @brief MauClient::writeNextData sends the given string to the server
 * @param data
 */
void MauClient::writeNextData(QString data)
{
    data.append("\n");
    server->write(data.toStdString().c_str());
}

/**
 * Called uppon a readyread signal is emited.
 * Reads all availavle data and processes it
 * @brief MauClient::readNextData reads available data
 */
void MauClient::readNextData()
{
    int availableBytes = server->bytesAvailable();
    while (availableBytes > 0) {
        char buff[1024] = { 0 };
        qint64 lineLength = server->readLine(buff, sizeof(buff));
        if (lineLength > 0) {
            handleMessage(QString(buff));
        }
        availableBytes = server->bytesAvailable();
    }
}
/**
 * Each message type has its defined order. Each part of a message is seperated by a semicolon.
 * The first part is the method type followed by MProtocol encoded parameters.
 * @brief MauClient::handleMessage handles a MProtocol encoded message and emits the corresponding singals
 * @param message the recived message
 */
void MauClient::handleMessage(QString message)
{

    message = message.trimmed();
    QStringList messageSplit = message.split(";");
    switch (messageSplit.at(0).toInt()) {
    case MProtocol::INIT_PLAYGROUND: {
        emit clientGameStarted();
        playerName = PLAYER::Name(messageSplit.at(1).toInt());
        std::map<PLAYER::Name, int> otherPlayerCardCount = MProtocol::stingToCardCountMap(messageSplit.at(3));
        for (unsigned i = 0; i < otherPlayerCardCount.size(); ++i) {
            localPlayerOrder.append(PLAYER::Name(i));
        }
        rotatePlayerMap();
        //        void initPlayground(const std::vector<Card> humanPlayerCards,
        //                            std::map<PLAYER::Name, int> otherPlayerCardCount,
        //                            const Card& topDepotCard,
        //                            Card::cardValue _wishSuitCard,
        //                            std::vector<std::string> playerNames);
        emit UIinitPlayground(MProtocol::stringToCardVec(messageSplit.at(2)),
                              otherPlayerCardCount,
                              MProtocol::stingToCard(messageSplit.at(4)),
                              Card::cardValue(messageSplit.at(5).toInt()),
                              getLocalPlayerNames(MProtocol::stringToStringVec(messageSplit.at(6))));
        break;
    }
    case MProtocol::DO_TURN:
        //        void UIdoTurn(std::vector<Card> playableCards,
        //                      Card::cardSuit wishedSuit);
        emit UIdoTurn(MProtocol::stringToCardVec(messageSplit.at(1)),
                      Card::cardSuit(messageSplit.at(2).toInt()));
        break;
    case MProtocol::OTHER_PLAYS_CARD:
        //        void UIplayerPlaysCard(PLAYER::Name pName,
        //                               const Card & playedCard);
        emit UIplayerPlaysCard(getLocalPlayerPosition(PLAYER::Name(messageSplit.at(1).toInt())),
                               MProtocol::stingToCard(messageSplit.at(2)));
        break;
    case MProtocol::OTHER_DRAWS_CARD:
        //        void UIplayerDrawsCard(PLAYER::Name pName);
        emit UIplayerDrawsCard(getLocalPlayerPosition(PLAYER::Name(messageSplit.at(1).toInt())));
        break;
    case MProtocol::ADD_CARD:
        //        void UIaddPlayerCard(const Card & card);
        emit UIaddPlayerCard(MProtocol::stingToCard(messageSplit.at(1)));
        break;
    case MProtocol::PLAYER_WON:
        //void UIPlayerWon(std::string _title);
        emit UIPlayerWon(messageSplit.at(1).toStdString());
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
        break;
    }
}
/**
 * @brief MauClient::rotatePlayerMap rotates the player order given by the server in order to have the local player on the bottom.
 */
void MauClient::rotatePlayerMap()
{
    std::rotate(localPlayerOrder.begin(), localPlayerOrder.begin() + playerName, localPlayerOrder.end());
}
/**
 * @brief MauClient::getLocalPlayerPosition returns the local player position differing to the remote player position
 * @param remoteName the remote position
 * @return the local player position differing to the remote player position
 */
PLAYER::Name MauClient::getLocalPlayerPosition(PLAYER::Name remoteName)
{
    return PLAYER::Name(localPlayerOrder.indexOf(remoteName));
}
/**
 * @brief MauClient::getLocalPlayerNames returns the vector of strings rotated like the rotated player map.
 * @param playerNames the local players position in the remote player order
 * @return the vector of strings rotated like the rotated player map.
 */
std::vector<std::string> MauClient::getLocalPlayerNames(std::vector<std::string> playerNames)
{
    std::vector<std::string> localPlayerNames = playerNames;
    std::rotate(localPlayerNames.begin(), localPlayerNames.begin() + playerName, localPlayerNames.end());
    return localPlayerNames;
}

MauClient::~MauClient()
{
    server->close();
}
