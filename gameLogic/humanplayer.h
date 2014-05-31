#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player {
public:
    explicit HumanPlayer();
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

#endif // HUMANPLAYER_H
