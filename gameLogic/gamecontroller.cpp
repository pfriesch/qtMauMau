#include "gamecontroller.h"

GameController::GameController(QObject *parent) :
  QObject(parent)
{
}

void GameController::playCard(Player &player, const Card &card)
{
  //TODO mb need to verify if this is a legal action
  player.dropCard(card);
  usedCards->pushCard(card);

}

void GameController::drawCard(Player &player)
{
  Card card;
  card = freshCards->getLast(usedCards);
  player.reciveCard(card);
}
