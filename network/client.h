#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include "gameLogic/Card.h"
#include "gameLogic/PlayerName.h"

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    void setupConnection(QString _address, QString _port);

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void UIplayerDrawsCard(PLAYER::Name pName);
    void UIaddPlayerCard(const Card& card);

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
};
#endif
