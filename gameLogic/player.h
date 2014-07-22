#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include "card.h"
#include "gamecontrollerproxy.h"
#include "PlayerNames.h"

class Player {
public:
protected:
    std::vector<Card> hand;
    std::string name;
    playerName pName;
    Card topCard;
    bool drewCard = false;
    GameControllerProxy gameController;

public:
    explicit Player(playerName pName, GameControllerProxy _gameController);

    virtual void otherPlaysCard(playerName pName, const Card& playedCard) = 0;
    virtual void otherDrawsCard(playerName pName) = 0;

    virtual void doTurn(Card::cardSuit wishSuitCard) = 0;
    virtual void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, playerName startingPlayer) = 0;
    virtual void reciveCard(const Card& card) = 0;
    virtual int getCardCount() const = 0;

    playerName getPName() const;

protected:
    std::vector<Card>& getPlayableCards(const Card& card, Card::cardSuit wishSuitCard = Card::NONE);
    void dropCard(const Card& card);
};

#endif // PLAYER_H
