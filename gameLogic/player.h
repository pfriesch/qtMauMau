#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"
#include "gamecontrollerproxy.h"

class Player {
public:
    enum playerName {
        BOTTOM = 0,
        LEFT = 1,
        TOP = 2,
        RIGHT = 3
    };

protected:
    std::vector<Card> hand;
    std::string name;
    Player::playerName pName;
    Card topCard;
    bool drewCard = false;
    GameControllerProxy* gameController;

public:
    explicit Player(Player::playerName pName);

    virtual void otherPlaysCard(Player::playerName pName, const Card& playedCard) = 0;
    virtual void otherDrawsCard(Player::playerName pName) = 0;

    virtual void doTurn(Card::cardSuit wishSuitCard, GameControllerProxy gcProxy) = 0;
    virtual void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, Player::playerName startingPlayer) = 0;
    virtual void reciveCard(const Card& card) = 0;
    virtual int getCardCount() const = 0;

    Player::playerName getPName() const;

protected:
    std::vector<Card>& getPlayableCards(const Card& card, Card::cardSuit wishSuitCard = Card::NONE);
};

#endif // PLAYER_H
