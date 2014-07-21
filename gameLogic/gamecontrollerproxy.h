#ifndef GAMECONTROLLERPROXY_H
#define GAMECONTROLLERPROXY_H

#include "card.h"

class GameController;
class GameControllerProxy {
private:
    GameController* gameContr;
    int playerID;

public:
    explicit GameControllerProxy(GameController* _gameContr, int _playerID);
    void playCard(const Card& card, Card::cardSuit whishedSuit = Card::NONE);
    void drawCard();
    void doNothing();
};

#endif // GAMECONTROLLERPROXY_H
