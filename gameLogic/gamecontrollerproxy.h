#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"
#include "PlayerName.h"

class GameController;

class GameControllerProxy {
private:
    GameController* gameContr;
    PLAYER::Name pName;

public:
    explicit GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName);
    void playCard(const Card& card, Card::cardSuit whishedSuit = Card::NONE);
    void drawCard();
};

#endif // GAMECONTROLLERPROXY_H
