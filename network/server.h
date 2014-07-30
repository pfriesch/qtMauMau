#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QHash>

class Server : public QObject {
    Q_OBJECT
public:
    Server(QObject* parent = 0);
    ~Server();
public
slots:
    void acceptConnection();
    void startRead();
    void send(int playerId, QString message);

private:
    QHash<int,QTcpSocket* > connections;
    QTcpServer server;
    QTcpSocket* client;
};

#endif
