#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QHash>

#include "gameLogic/remoteplayer.h"

class Server : public QObject {
    Q_OBJECT
public:
    Server(QObject* parent = 0);
    ~Server();
public
slots:
    void startServer(int playerCount = 3);
    void acceptConnection();
    void startRead();
    void send(int playerId, QString message);

signals:
    void newConnection(QString adress, int connectionIndex, QString name);

private:
    QVector<RemotePlayer*> players;
    QHash<int, QTcpSocket*> connections;
    QTcpServer server;
};

#endif
