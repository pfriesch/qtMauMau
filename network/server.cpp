#include "server.h"
#include <iostream>
#include <settings.h>
#include "maumauprotokoll.h"

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
    int count = clients.size();
    if (count < 3) {
        connect(client, &QTcpSocket::readyRead, this, &Server::readNextData);
        clients.insert(PLAYER::Name(count + 1), client);
        emit newConnection(client->peerAddress().toString(), count, "hans");
    } else {
        client->write("error max user");
        client->flush();
    }

    //connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::readNextData()
{

    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());

    PLAYER::Name name = clients.key(client);

    QString message = client->readLine();
    qDebug() << "send Data: " << message;
    QStringList messageSplit = message.split(";");
    switch (MMP::toServer(messageSplit.at(0).toInt())) {
    case MMP::PLAY_CARD:
        emit RemotePlaysCard(name, MMP::stingToCard(messageSplit.at(1)));
        break;
    case MMP::DRAW_CARD:
        emit RemoteDrawsCard(name);
        break;
    default:
        qDebug() << "method not found";
        break;
    }
}
QHash<PLAYER::Name, QTcpSocket*> Server::getClients() const
{
    return clients;
}

void Server::RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card>& remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer)
{
    QString message;
    message.append(QString::number(MMP::INIT_PLAYGROUND));
    message.append(";");
    message.append(MMP::cardVectorToSting(remotePlayerCards));
    message.append(";");
    message.append(MMP::playerCardCountToSting(otherPlayerCardCount));
    message.append(";");
    message.append(MMP::cardToSting(topDepotCard));
    message.append(";");
    message.append(QString::number(startingPlayer));
    writeNextData(message, clients[remotePlayerName]);
}

void Server::RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishSuitCard)
{
    QString message;
    message.append(QString::number(MMP::DO_TURN));
    message.append(";");
    message.append(MMP::cardVectorToSting(playableCards));
    message.append(";");
    message.append(QString::number(wishSuitCard));
    writeNextData(message, clients[remotePlayerName]);
}

void Server::RemotePlayerPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    QString message;
    message.append(QString::number(MMP::OTHER_PLAYS_CARD));
    message.append(";");
    message.append(QString::number(pName));
    message.append(";");
    message.append(MMP::cardToSting(playedCard));
    foreach(QTcpSocket * client, clients)
    {
        writeNextData(message, client);
    }
}

void Server::RemotePlayerDrawsCard(PLAYER::Name pName)
{
    QString message;
    message.append(QString::number(MMP::OTHER_PLAYS_CARD));
    message.append(";");
    message.append(QString::number(pName));
    foreach(QTcpSocket * client, clients)
    {
        writeNextData(message, client);
    }
}

void Server::RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card)
{
    QString message;
    message.append(QString::number(MMP::ADD_CARD));
    message.append(";");
    message.append(MMP::cardToSting(card));
    writeNextData(message, clients[remotePlayerName]);
}

void Server::writeNextData(QString data, QTcpSocket* client)
{
    qDebug() << "send Data: " << data;
    qint64 writtenByteCount = client->write(data.toStdString().c_str());
    if (writtenByteCount == -1 || writtenByteCount < qstrlen(data.toStdString().c_str())) {
        //TODO handle network fail
        qDebug() << "server -> client write failed";
    }
}

Server::~Server()
{
    server.close();
}
