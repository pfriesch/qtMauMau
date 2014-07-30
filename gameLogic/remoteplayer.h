#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "player.h"

class RemotePlayer : public Player {
public:
    explicit RemotePlayer(PLAYER::Name pName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

};

#endif // REMOTEPLAYER_H
