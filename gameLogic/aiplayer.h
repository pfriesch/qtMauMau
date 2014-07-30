#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(PLAYER::Name pName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

};

#endif // AIPLAYER_H
