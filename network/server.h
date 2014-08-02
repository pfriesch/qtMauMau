#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QHash>

#include "gameLogic/remoteplayer.h"
#include "gameLogic/PlayerName.h"

class Server : public QObject {
    Q_OBJECT
public:
    Server(QObject* parent = 0);
    ~Server();
    QHash<PLAYER::Name, QTcpSocket*> getClients() const;

public
slots:
    void acceptConnection();
    void readNextData();
//    void startRead();
//    void send(int playerId, QString message);

signals:
    void newConnection(QString adress, int connectionIndex, QString name);

private:
    QHash<PLAYER::Name, QTcpSocket*> clients;
    QTcpServer server;
    void writeNextData(QString data, QTcpSocket* client);

public
slots:
    void RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card>& remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer);
    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void RemotePlayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void RemotePlayerDrawsCard(PLAYER::Name pName);
    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);

signals:
    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card);
    void RemoteDrawsCard(PLAYER::Name remotePlayerName);
};

#endif
