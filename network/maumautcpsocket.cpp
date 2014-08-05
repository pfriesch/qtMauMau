#include "maumautcpsocket.h"

MTcpSocket::MTcpSocket(QTcpSocket socket)
    : QTcpSocket(parent)
{
}
PLAYER::Name MTcpSocket::getPlayerName() const
{
    return playerName;
}

void MTcpSocket::setPlayerName(const PLAYER::Name& value)
{
    playerName = value;
}
