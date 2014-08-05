#ifndef MSOCKET_H
#define MSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "gameLogic/PlayerName.h"

class MSocket : public QObject {
    Q_OBJECT
public:
    explicit MSocket(QTcpSocket* _socket, QObject* parent = 0);
    QTcpSocket* getSocket() const;

    PLAYER::Name getPlayerName() const;
    void setPlayerName(const PLAYER::Name& value);

signals:
    void readyRead(MSocket* client);

private
slots:
    void socketReadyRead();

private:
    QTcpSocket* socket;
    PLAYER::Name playerName = PLAYER::Name(0);
};

#endif // MSOCKET_H
