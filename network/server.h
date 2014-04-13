#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include "settings.h"

class Server : public QObject
{
    Q_OBJECT
public:
    //the server should send and get messages, we have to build a client and a server together.
    explicit Server(QObject * parent = 0);
    Server(void);
    void write();
    bool listen();
    ~Server();

private:
    QTcpServer server;
signals:

public slots:
  void read();
};

#endif // SERVER_H
