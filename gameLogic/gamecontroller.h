#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"


class GameController
{
private:
  QVector<Player> players;
  //The stack of cards where cards are taken if a player has to draw.
  Deck cardStack;
  //The stack of cards where the played cards are dropped.
  Deck cardDepot;

public:
  void startGame();
  void doTurn(Player &player);
  void playCard(Player &player, const Card &card);
  void drawCard(Player &player);
};

#endif // GAMECONTROLLER_H
