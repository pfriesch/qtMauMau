#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"

using namespace std;

class Player {
private:
    vector<Card> hand;
    string name;

public:
    virtual void gameInit(vector<Card>& hand, Card& topCard, vecotr<int> otherPlayerCardCount);
    virtual void reciveCard(const Card& card);
    virtual void dropCard(const Card& card);
    virtual vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    virtual vector<Card> getHand() const;
    virtual int getCardCount() const;
    virtual Player::PlayerType getType() const;
};

#endif // PLAYER_H
