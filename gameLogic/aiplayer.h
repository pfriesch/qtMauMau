#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(playerName pName, GameControllerProxy _gameController);
    void otherPlaysCard(playerName pName, const Card& playedCard);
    void otherDrawsCard(playerName pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, playerName startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;
};

#endif // AIPLAYER_H
