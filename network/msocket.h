#ifndef MSOCKET_H
#define MSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "gameLogic/playername.h"
/**
 * @brief The MSocket class a wrapper class around a QTcpSocket to identify it when a readyread signal is emited
 */
class MSocket : public QObject {
    Q_OBJECT
public:
    explicit MSocket(QTcpSocket* _socket);
    ~MSocket();
    QTcpSocket* getSocket() const;

    PLAYER::Name getPlayerName() const;
    void setPlayerName(const PLAYER::Name& value);

    QString getName() const;
    void setName(const QString& value);

signals:
    void readyRead(MSocket* client);

private
slots:
    void socketReadyRead();

private:
    QTcpSocket* socket;
    PLAYER::Name playerName = PLAYER::NONE;
    QString name;
};

#endif // MSOCKET_H
