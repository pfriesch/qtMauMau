#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(int playerId);
    void otherPlaysCard(int playerId, const Card& playedCard);
    void otherDrawsCard(int playerId);

    void doTurn();
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;
};

#endif // AIPLAYER_H
