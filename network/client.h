#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "gameLogic/Card.h"
#include "gameLogic/PlayerName.h"

class MauClient : public QObject {
    Q_OBJECT
public:
    MauClient(QObject* parent = 0);
    ~MauClient();
    //name of the player in the remote game controller
    PLAYER::Name playerName;
    void setupConnection(QString _address, QString _port);
    PLAYER::Name getLocalPlayerName(PLAYER::Name pName);

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void UIplayerDrawsCard(PLAYER::Name pName);
    void UIaddPlayerCard(const Card& card);

    void gameStarted();

public
slots:
    void UIplaysCard(const Card& card);
    void UIdrawsCard();

private
slots:
    void readNextData();
    void OnError();

private:
    QTcpSocket* server = new QTcpSocket();
    void writeNextData(QString data);
    void handleMessage(QString message);
    std::map<PLAYER::Name, int> rotatePlayerMap(std::map<PLAYER::Name, int> otherPlayerCardCount);
};
#endif
