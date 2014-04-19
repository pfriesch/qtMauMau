#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include "Card.h"
#include "Deck.h"

class Player
{
private:
  bool human;
  QVector<Card> hand;
public:
  Player(bool is_human);
  int getnumberOfCards() const;
  void reciveCard(Card card);
  bool wantToPlayCard() const;
};

#endif // PLAYER_H
