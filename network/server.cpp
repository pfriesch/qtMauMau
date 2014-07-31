#include "server.h"
#include <iostream>
#include <settings.h>

Server::Server(QObject* parent)
    : QObject(parent)
{
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    int port(Settings::getInstance()->getProperty("network/port").toInt());
    server.listen(QHostAddress::Any, port);
    qDebug() << "Server is now listening";
}

void Server::acceptConnection()
{
    qDebug() << "Server acceptedConection";
    QTcpSocket* client = server.nextPendingConnection();
    int index = connections.size();
    if (index < 3) {
        connections.insert(index, client);
        emit newConnection(client->peerAddress().toString(), index, "hans");
    } else {
        client->write("error max user");
        client->flush();
    }

    //connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card> &remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card &topDepotCard, PLAYER::Name startingPlayer)
{

}

void Server::RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishSuitCard)
{

}

void Server::RemotePlayerPlaysCard(PLAYER::Name pName, const Card &playedCard)
{

}

void Server::RemotePlayerDrawsCard(PLAYER::Name pName)
{

}

void Server::RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card &card)
{

}
QHash<int, QTcpSocket*> Server::getConnections() const
{
    return connections;
}

//void Server::startRead()
//{
//    qDebug() << "start reading from Client";

//    char buffer[1024] = { 0 };
//    connections[0]->read(buffer, connections[0]->bytesAvailable());
//    qDebug() << buffer;
//    //we have to write the buffer to an object or something,
//    //not implemented yet!!
//}

//void Server::send(int playerId, QString message)
//{

//    QTcpSocket* connection = connections.value(1);
//    connection->write(message.toStdString().c_str());
//    connection->flush();
//}

Server::~Server()
{
    server.close();
}
