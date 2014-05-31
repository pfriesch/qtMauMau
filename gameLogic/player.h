#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <string>
#include <vector>
#include "card.h"


class Player : public QObject {
    Q_OBJECT
private:
    vector<Card> hand;
    string name;
    int playerId;

public
slots:
    virtual void playerPlaysCard(int playerId, const Card& playedCard);
    virtual void playerDrawsCard(int playerId);
signals:
    void playCard(int playerId, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(int playerId);
    void doNothing(int playerId);

public:
    virtual void addCard(const Card& card);
    virtual void doTurn();
    virtual void gameInit(const vector<Card>& hand, const Card& topCard, vector<int> otherPlayerCardCount);
    virtual void reciveCard(const Card& card);
    virtual vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    virtual vector<Card> getHand() const;
    virtual int getCardCount() const;
    virtual void dropCard(const Card& card);
};

#endif // PLAYER_H
