#include "gamecontrollerproxy.h"
#include "gamecontroller.h"

GameControllerProxy::GameControllerProxy(GameController* _gameContr, int _playerID)
    : gameContr(_gameContr)
    , playerID(_playerID)
{
}

void GameControllerProxy::playCard(const Card& card, Card::cardSuit whishedSuit)
{
}

void GameControllerProxy::drawCard()
{
}

void GameControllerProxy::doNothing()
{
}
