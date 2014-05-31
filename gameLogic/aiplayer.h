#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(int playerId);
    void playerPlaysCard(int playerId, const Card& playedCard);
    void playerDrawsCard(int playerId);

    void addCard(const Card& card);
    void doTurn();
    void gameInit(const vector<Card>& hand, const Card& topCard, vector<int> otherPlayerCardCount);
    void reciveCard(const Card& card);
    vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    vector<Card> getHand() const;
    int getCardCount() const;
    void dropCard(const Card& card);
};

#endif // AIPLAYER_H
