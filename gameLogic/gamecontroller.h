#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "deck.h"
#include "player.h"


class GameController : public QObject
{
  Q_OBJECT
private:
  QVector *players;
  Deck *freshCards;
  Deck *usedCards;


public:
  explicit GameController(QObject *parent = 0);

signals:
  void doTurn(Player player);

public slots:
  void playCard(Player &player, const Card &card);
  void drawCard(Player &player);

};

#endif // GAMECONTROLLER_H
