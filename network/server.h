#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QList>

#include "gameLogic/remoteplayer.h"
#include "gameLogic/PlayerName.h"
#include "msocket.h"

class MauServer : public QObject {
    Q_OBJECT
public:
    MauServer(QObject* parent = 0);
    ~MauServer();
    QList<MSocket*> getClients() const;

public
slots:
    void acceptConnection();
    void readNextData(MSocket* client);
//    void startRead();
//    void send(int playerId, QString message);

signals:
    void newConnection(QString adress, int connectionIndex, QString name);

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

private:
    QList<MSocket*> clients;

    QTcpServer server;
    void writeNextData(QString data, QTcpSocket* client);
    QTcpSocket* socketByName(PLAYER::Name pName);
    void assignSocket(PLAYER::Name remotePlayerName);
};

#endif
