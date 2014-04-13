#include "networkmanager.h"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
}


void NetworkManager::connectTo(quint32 ip){

    //const QHostAddress hostIP(ip);

    //QString port = Settings::getInstance()->getProperty("Port");
    //QTcpSocket *socket = new QTcpSocket();
}
