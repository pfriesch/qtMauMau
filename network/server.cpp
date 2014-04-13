#include "server.h"

Server::Server(QObject* parent): QObject(parent)
{
    //Everytime a client connects, read() is called
    connect(&server, SIGNAL(newConnection()),this, SLOT(read()));

    quint16 port = Settings::getInstance()->getProperty("network/port").toInt();

    if(!server.listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }
}

void Server::read(){
    QTcpSocket *socket = server.nextPendingConnection();
    char buffer[1024] = {0};
    socket->read(buffer, socket->bytesAvailable());
    qDebug() << buffer;
    socket->close();
}

void Server::write(){
    QTcpSocket *socket = server.nextPendingConnection();
    QString message("response");
    socket->write(message.toStdString().c_str(),message.length());
}


Server::~Server(){
    server.close();
}
