#include "msocket.h"

MSocket::MSocket(QTcpSocket* _socket, QObject* parent)
    : socket(_socket)
    , QObject(parent)
{

    connect(socket, &QTcpSocket::readyRead, this, &MSocket::socketReadyRead);
}
QTcpSocket* MSocket::getSocket() const
{
    return socket;
}

void MSocket::socketReadyRead()
{
    emit readyRead(this);
}
PLAYER::Name MSocket::getPlayerName() const
{
  return playerName;
}

void MSocket::setPlayerName(const PLAYER::Name &value)
{
  playerName = value;
}


