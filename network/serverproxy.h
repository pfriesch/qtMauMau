#ifndef SERVERPROXY_H
#define SERVERPROXY_H

#include "gameLogic/Card.h"
#include "gameLogic/PlayerName.h"

class Server;

class ServerProxy {
private:
    Server* server;
    PLAYER::Name pName;

public:
    explicit ServerProxy(Server* _gameContr, PLAYER::Name _pName);
    void playCard(const Card& card, Card::cardSuit whishedSuit = Card::NONE);
    void drawCard();
};

#endif // SERVERPROXY_H
