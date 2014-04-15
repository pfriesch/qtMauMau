#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void start(QString address, quint16 port);
    ~Client();

private:
  QTcpSocket client;
signals:

public slots:
  void startTransfer();
};

#endif // CLIENT_H
