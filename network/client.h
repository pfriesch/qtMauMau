#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    void setupConnection(QString _address, QString _port);
public
slots:
    void write();
   // void read();
    void OnError();

private:
    QTcpSocket *client = new QTcpSocket();
};
#endif
