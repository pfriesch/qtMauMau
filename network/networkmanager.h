#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QFlags>
#include "../settings.h"
#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = 0);
    void connectTo(quint32 ip);
    //void getNetworkConnection();
    //void closeConnection();

signals:

public slots:

};

#endif // NETWORKMANAGER_H
