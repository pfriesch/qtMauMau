#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Card.h"

class Player : public QObject
{
  Q_OBJECT
public:
  explicit Player(QObject *parent = 0);

signals:
  void playCard(const Card &card);
  void wishSuit(Card::cardSuit suit);

public slots:
  void doTurn();
  void reciveCard(const Card card);

};

#endif // PLAYER_H
