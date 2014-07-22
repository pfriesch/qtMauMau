#include "gamecontrollerproxy.h"
#include "gamecontroller.h"

GameControllerProxy::GameControllerProxy(GameController* _gameContr, playerName _pName)
    : gameContr(_gameContr)
    , pName(_pName)
{
}

void GameControllerProxy::playCard(const Card& card, Card::cardSuit whishedSuit)
{
    gameContr->playCard(pName, card, whishedSuit);
}

void GameControllerProxy::drawCard()
{
    gameContr->drawCard(pName);
}

void GameControllerProxy::doNothing()
{
    gameContr->doNothing(pName);
}
