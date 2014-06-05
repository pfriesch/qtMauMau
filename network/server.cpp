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
    client = server.nextPendingConnection();
    connections.insert(1,client);

    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

void Server::startRead()
{
    qDebug() << "start reading from Client";

    char buffer[1024] = { 0 };
    client->read(buffer, client->bytesAvailable());
    qDebug() << buffer;
    //we have to write the buffer to an object or something,
    //not implemented yet!!
}

void Server::send(int playerId, QString message)
{

    QTcpSocket *connection = connections.value(1);
    connection->write(message.toStdString().c_str());
    connection->flush();
}

Server::~Server()
{
    server.close();
}
