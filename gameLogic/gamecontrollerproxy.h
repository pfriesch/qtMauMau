#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"
#include "PlayerNames.h"

class GameController;

class GameControllerProxy {
private:
    GameController* gameContr;
    playerName pName;

public:
    explicit GameControllerProxy(GameController* _gameContr, playerName _pName);
    void playCard(const Card& card, Card::cardSuit whishedSuit = Card::NONE);
    void drawCard();
    void doNothing();
};

#endif // GAMECONTROLLERPROXY_H
