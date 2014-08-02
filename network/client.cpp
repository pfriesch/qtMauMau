#include "client.h"
#include <QHostAddress>
#include <settings.h>
#include "maumauprotokoll.h"

Client::Client(QObject* parent)
    : QObject(parent)
{
}

void Client::setupConnection(QString _address, QString _port)
{
    QHostAddress address = QHostAddress(_address);
    qint16 port = _port.toInt();

    server->connectToHost(address, port);

    //connect(client, SIGNAL(connected()), this, SLOT(write()));
    connect(server, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError()));
    connect(server, &QTcpSocket::readyRead, this, &Client::readNextData);
    //connect(&client, SIGNAL(readyRead()), this, SLOT(read()));
}

void Client::OnError()
{
    qDebug() << "socket error";
}

void Client::UIplaysCard(const Card& card)
{
    QString message;
    message.append(MMP::PLAY_CARD);
    message.append(";");
    message.append(MMP::cardToSting(card));
    writeNextData(message);
}

void Client::UIdrawsCard()
{
    QString message;
    message.append(MMP::DRAW_CARD);
    writeNextData(message);
}

void Client::readNextData()
{
    char buf[1024];
    qint64 lineLength = server->readLine(buf, sizeof(buf));
    if (lineLength != -1) {
        handleMessage(QString(buf));
    }
}

void Client::writeNextData(QString data)
{
    qDebug() << "send Data: " << data;
    qint64 writtenByteCount = server->write(data.toStdString().c_str());
    if (writtenByteCount == -1 || writtenByteCount < qstrlen(data.toStdString().c_str())) {
        //TODO handle network fail
        qDebug() << "client -> server write failed";
    }
}

void Client::handleMessage(QString message)
{
    QStringList messageSplit = message.split(";");
    switch (messageSplit.at(0).toInt()) {
    case MMP::INIT_PLAYGROUND:
        emit UIinitPlayground(MMP::stringToCardVec(messageSplit.at(1)), MMP::stingToCardCountMap(messageSplit.at(2)), MMP::stingToCard(messageSplit.at(3)), PLAYER::Name(messageSplit.at(4).toInt()));
        break;
    case MMP::DO_TURN:
        emit UIdoTurn(MMP::stringToCardVec(messageSplit.at(1)), Card::cardSuit(messageSplit.at(2).toInt()));
        break;
    case MMP::OTHER_PLAYS_CARD:
        emit UIplayerPlaysCard(PLAYER::Name(messageSplit.at(1).toInt()), MMP::stingToCard(messageSplit.at(2)));
        break;
    case MMP::OTHER_DRAWS_CARD:
        emit UIplayerDrawsCard(PLAYER::Name(messageSplit.at(1).toInt()));
        break;
    case MMP::ADD_CARD:
        emit UIaddPlayerCard(MMP::stingToCard(messageSplit.at(1)));
        break;
    default:
        qDebug() << "method not found";
        break;
    }
}
/*
void Client::read(){

    if (client.error()) {
        qCritical() << client.error();
        qCritical() << client.errorString();
        qCritical() << client.state();

    }

    qDebug() << "start reading from Server";

    char buffer[1024] = { 0 };
    client.read(buffer, client.bytesAvailable());
    qDebug() << buffer;
}*/

Client::~Client()
{
    server->close();
}
