#include "server.h"
#include <iostream>
#include <settings.h>
#include "maumauprotokoll.h"

/**
 * @brief MauServer::MauServer sets the server to listen
 * @param parent
 */
MauServer::MauServer(QObject* parent)
    : QObject(parent)
{
    connect(&server, &QTcpServer::newConnection, this, &MauServer::acceptNewConnection);

    int port(Settings::getInstance()->getProperty("network/port").toInt());
    server.listen(QHostAddress::Any, port);
}
/**
 * @brief MauServer::acceptNewConnection accepts a connection and sets it to pending connections
 */
void MauServer::acceptNewConnection()
{
    QTcpSocket* client = server.nextPendingConnection();
    pendingConnections.append(new MSocket(client));
    connect(pendingConnections.back(), &MSocket::readyRead, this, &MauServer::readNextData);
    QString message;
    message.append(QString::number(MProtocol::REQUEST_NAME));
    message.append(";");
    message.append(QString::number(pendingConnections.size() - 1));
    writeData(message, client);
}
/**
 * @brief MauServer::readNextData called when a readyread signal is emited. Reads all available data
 * @param _client the client to read from
 */
void MauServer::readNextData(MSocket* _client)
{

    QTcpSocket* client = _client->getSocket();

    PLAYER::Name name = _client->getPlayerName();

    int availableBytes = client->bytesAvailable();
    while (availableBytes > 0) {
        char buff[1024] = { 0 };
        qint64 lineLength = client->readLine(buff, sizeof(buff));
        if (lineLength > 0) {
            handleMessage(name, QString(buff));
        } else {
            qDebug() << "message length error occured";
        }
        availableBytes = client->bytesAvailable();
    }
}
/**
 * @brief MauServer::handleMessage handles a given string and emits signals accordingly
 * @param name the player who send the message
 * @param message
 */
void MauServer::handleMessage(PLAYER::Name name, QString message)
{
    message = message.trimmed();
    QStringList messageSplit = message.split(";");
    switch (MProtocol::toServer(messageSplit.at(0).toInt())) {
    case MProtocol::PLAY_CARD:
        emit RemotePlaysCard(name, MProtocol::stingToCard(messageSplit.at(1)), Card::cardSuit(messageSplit.at(2).toInt()));
        break;
    case MProtocol::DRAW_CARD:
        emit RemoteDrawsCard(name);
        break;
    case MProtocol::SEND_NAME: {
        MSocket* client = pendingConnections.at(messageSplit.at(1).toInt());
        client->setName(messageSplit.at(2));
        emit newConnection(client->getSocket()->peerAddress().toString(), messageSplit.at(1).toInt(), client->getName());
        break;
    }
    default:
        break;
    }
}
/**
 * @brief MauServer::rejectConnection called when a pending connection is rejceted
 * @param pendingConIndex the index of the connection to be rejected
 */
void MauServer::rejectConnection(int pendingConIndex)
{
    MSocket* client = pendingConnections.at(pendingConIndex);
    QString message;
    message.append(QString::number(MProtocol::CONNECTION_REJECTED));
    writeData(message, client->getSocket());
    disconnect(client, &MSocket::readyRead, this, &MauServer::readNextData);
    delete client;
    pendingConnections.removeAt(pendingConIndex);
}
/**
 * @brief MauServer::acceptConnection called when a pendig connection is accepted
 * @param pendingConIndex the index of the connection the be accepted
 */
void MauServer::acceptConnection(int pendingConIndex)
{
    MSocket* client = pendingConnections.at(pendingConIndex);
    clients.append(client);
    QString message;
    message.append(QString::number(MProtocol::CONNECTION_ACCEPTED));
    writeData(message, client->getSocket());
    pendingConnections.removeAt(pendingConIndex);
}
/**
 * @brief MauServer::getClients
 * @return
 */
QList<MSocket*> MauServer::getClients() const
{
    return clients;
}
/**
 * @brief MauServer::RemoteInitPlayground constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param remotePlayerCards
 * @param otherPlayerCardCount
 * @param topDepotCard
 * @param _wishSuitCard
 * @param playerNames
 */
void MauServer::RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card> remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames)
{
    assignSocket(remotePlayerName);
    QString message;
    message.append(QString::number(MProtocol::INIT_PLAYGROUND));
    message.append(";");
    message.append(QString::number(remotePlayerName));
    message.append(";");
    message.append(MProtocol::cardVectorToSting(remotePlayerCards));
    message.append(";");
    message.append(MProtocol::playerCardCountToSting(otherPlayerCardCount));
    message.append(";");
    message.append(MProtocol::cardToSting(topDepotCard));
    message.append(";");
    message.append(QString::number(_wishSuitCard));
    message.append(";");
    message.append(MProtocol::stringVecToSingle(playerNames));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::RemoteDoTurn constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param playableCards
 * @param wishedSuit
 */
void MauServer::RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishedSuit)
{
    QString message;
    message.append(QString::number(MProtocol::DO_TURN));
    message.append(";");
    message.append(MProtocol::cardVectorToSting(playableCards));
    message.append(";");
    message.append(QString::number(wishedSuit));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::RemotePlayerPlaysCard constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param pName
 * @param playedCard
 */
void MauServer::RemotePlayerPlaysCard(PLAYER::Name remotePlayerName, PLAYER::Name pName, const Card& playedCard)
{
    QString message;
    message.append(QString::number(MProtocol::OTHER_PLAYS_CARD));
    message.append(";");
    message.append(QString::number(pName));
    message.append(";");
    message.append(MProtocol::cardToSting(playedCard));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::RemotePlayerDrawsCard constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param pName
 */
void MauServer::RemotePlayerDrawsCard(PLAYER::Name remotePlayerName, PLAYER::Name pName)
{
    QString message;
    message.append(QString::number(MProtocol::OTHER_DRAWS_CARD));
    message.append(";");
    message.append(QString::number(pName));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::RemoteAddPlayerCard constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param card
 */
void MauServer::RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card)
{
    QString message;
    message.append(QString::number(MProtocol::ADD_CARD));
    message.append(";");
    message.append(MProtocol::cardToSting(card));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::RemotePlayerWon constructs a MProtocol message of the slot type and sends it
 * @param remotePlayerName
 * @param _title
 */
void MauServer::RemotePlayerWon(PLAYER::Name remotePlayerName, std::string _title)
{
    QString message;
    message.append(QString::number(MProtocol::PLAYER_WON));
    message.append(";");
    message.append(QString(_title.c_str()));
    writeData(message, socketByName(remotePlayerName));
}
/**
 * @brief MauServer::writeData writes the given string to the given socket
 * @param data
 * @param client
 */
void MauServer::writeData(QString data, QTcpSocket* client)
{
    data.append("\n");
    client->write(data.toStdString().c_str());
}
/**
 * @brief MauServer::socketByName returns the socket wich is connected to the given player name
 * @param pName
 * @return the socket wich is connected to the given player name
 */
QTcpSocket* MauServer::socketByName(PLAYER::Name pName)
{
    for (int i = 0; i < clients.size(); ++i) {
        if (clients.at(i)->getPlayerName() == pName) {
            return clients.at(i)->getSocket();
        }
    }
    return NULL;
}
/**
 * @brief MauServer::assignSocket assigns the next free socket to the given name
 * @param remotePlayerName
 */
void MauServer::assignSocket(PLAYER::Name remotePlayerName)
{
    for (int i = 0; i < clients.size(); ++i) {
        if (clients.at(i)->getPlayerName() == PLAYER::NONE) {
            clients.at(i)->setPlayerName(remotePlayerName);
            break;
        }
    }
}

MauServer::~MauServer()
{
    for (int i = 0; i < pendingConnections.size(); ++i) {
        delete pendingConnections.at(i);
    }
    for (int i = 0; i < clients.size(); ++i) {
        delete clients.at(i);
    }
    server.close();
}
