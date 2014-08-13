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
    void acceptNewConnection();
    void readNextData(MSocket* client);
    void handleMessage(PLAYER::Name name, QString message);
    void rejectConnection(int pendingConIndex);
    void acceptConnection(int pendingConIndex);
//    void startRead();
//    void send(int playerId, QString message);

signals:
    void newConnection(QString adress, int connectionIndex, QString name);

public
slots:
    void RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card>& remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames);
    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    void RemotePlayerPlaysCard(PLAYER::Name remotePlayerName, PLAYER::Name pName, const Card& playedCard);
    void RemotePlayerDrawsCard(PLAYER::Name remotePlayerName, PLAYER::Name pName);
    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);
    void RemotePlayerWon(PLAYER::Name remotePlayerName, PLAYER::Name pName);

signals:
    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, Card::cardSuit wishedSuit);
    void RemoteDrawsCard(PLAYER::Name remotePlayerName);

private:
    QList<MSocket*> pendingConnections;
    QList<MSocket*> clients;

    QTcpServer server;
    void writeData(QString data, QTcpSocket* client);
    QTcpSocket* socketByName(PLAYER::Name pName);
    void assignSocket(PLAYER::Name remotePlayerName);
};

#endif
