#include "client.h"
#include <QHostAddress>
#include <settings.h>

Client::Client(QObject* parent)
    : QObject(parent)
{
    connect(&client, SIGNAL(connected()), this, SLOT(write()));
    connect(&client, SIGNAL(readyRead()), this, SLOT(read()));
}

void Client::setupConnection(QHostAddress address)
{
    int port(Settings::getInstance()->getProperty("network/port").toInt());

    client.connectToHost(address, port);

    if (client.error()) {
        qCritical() << client.error();
        qCritical() << client.errorString();
    }
}

void Client::write()
{
    //write HelloWorld is just a dummy
    client.write("Hello, world", 13);
}

void Client::read(){
    qDebug() << "start reading from Server";

    char buffer[1024] = { 0 };
    client.read(buffer, client.bytesAvailable());
    qDebug() << buffer;
}

Client::~Client()
{
    client.close();
}
