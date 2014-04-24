#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "deck.h"
#include "player.h"


class GameController : public QObject
{
  Q_OBJECT
private:
  QVector<Player> players;
  //The stack of cards where cards are taken if a player has to draw.
  Deck cardStack;
  //The stack of cards where the played cards are dropped.
  Deck cardDepot;


public:
  explicit GameController(QObject *parent = 0);

signals:
  void doTurn(Player &player);

public slots:
  void playCard(Player &player, const Card &card);
  void drawCard(Player &player);

};

#endif // GAMECONTROLLER_H
