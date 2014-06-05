#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <string>
#include <vector>
#include "card.h"

using namespace std;

class Player : public QObject {
    Q_OBJECT
private:
    vector<Card> hand;
    string name;
    int playerId;

public
slots:
    virtual void playerPlaysCard(int playerId, const Card& playedCard) =0;
    virtual void playerDrawsCard(int playerId) =0;
signals:
    void playCard(int playerId, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(int playerId);
    void doNothing(int playerId);

public:
    virtual void addCard(const Card& card) =0;
    virtual void doTurn() =0;
    virtual void gameInit(const vector<Card>& hand, const Card& topCard, vector<int> otherPlayerCardCount) =0;
    virtual void reciveCard(const Card& card) =0;
    virtual vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard) =0;
    virtual vector<Card> getHand() const =0;
    virtual int getCardCount() const =0;
    virtual void dropCard(const Card& card) =0;
};

#endif // PLAYER_H
