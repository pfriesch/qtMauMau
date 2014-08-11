#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player {
public:
    explicit AIPlayer(PLAYER::Name playerName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name playerName);
    void doTurn(Card::cardSuit wishedSuit);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer);
    void reciveCard(const Card& card);
    void playerWon(PLAYER::Name playerName);

private:
    Card getPlayCard(std::vector<Card> playableCards);
    Card::cardSuit getWhishedCardSuit();
};

#endif // AIPLAYER_H
