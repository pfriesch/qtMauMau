#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"
#ifdef TEST
#include "gameLogic/Test/aiplayer_test.h"
#endif

class AIPlayer : public Player {
#ifdef TEST
    friend class AIPlayer_test;
#endif
public:
    explicit AIPlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);
    void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name playerName);
    void doTurn(Card topCard, Card::cardSuit wishedSuit);
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  Card::cardValue _wishSuitCard,
                  std::vector<std::string> playerNames);
    void reciveCard(const Card& card);
    void playerWon(std::string _title);

private:
    Card getPlayCard(std::vector<Card> playableCards);
    Card::cardSuit getWhishedCardSuit();
};

#endif // AIPLAYER_H
