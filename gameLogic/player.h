#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include "card.h"
#include "gamecontrollerproxy.h"
#include "PlayerName.h"

static const int MAX_PLAYER = 4;
static const int MIN_PLAYER = 2;

class Player {
public:
    enum Type {
        HUMAN_PLAYER = 0,
        AI_PLAYER = 1,
        REMOTE_PLAYER = 2
    };

protected:
    std::vector<Card> hand;
    std::string name;
    PLAYER::Name playerName;
    Card topCard;
    GameControllerProxy gameController;

public:
    explicit Player(PLAYER::Name playerName, GameControllerProxy _gameController);

    virtual void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard) = 0;
    virtual void otherDrawsCard(PLAYER::Name playerName) = 0;

    virtual void doTurn(Card::cardSuit wishedSuit) = 0;
    virtual void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer) = 0;
    virtual void reciveCard(const Card& card) = 0;
    virtual void playerWon(PLAYER::Name playerName) = 0;

    PLAYER::Name getPName() const;

    int getCardCount() const;

protected:
    std::vector<Card> getPlayableCards(const Card& card, Card::cardSuit wishedSuit);
    void dropCard(const Card& card);
};

#endif // PLAYER_H
