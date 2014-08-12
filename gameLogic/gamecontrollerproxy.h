#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"
#include "PlayerName.h"

class GameController;

class GameControllerProxy {
private:
    GameController* gameContr;
    PLAYER::Name pName;
    Card::cardValue whishSuitCard;

public:
    explicit GameControllerProxy(GameController* _gameContr, PLAYER::Name _pName);
    void playCard(const Card& card, Card::cardSuit whishedSuit);
    void drawCard();

};

#endif // GAMECONTROLLERPROXY_H
