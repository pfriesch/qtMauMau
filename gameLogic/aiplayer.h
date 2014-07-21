#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(Player::playerName pName);
    void otherPlaysCard(Player::playerName pName, const Card& playedCard);
    void otherDrawsCard(Player::playerName pName);
    void doTurn(Card::cardSuit wishSuitCard, GameControllerProxy gcProxy);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, Player::playerName startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;
};

#endif // AIPLAYER_H
