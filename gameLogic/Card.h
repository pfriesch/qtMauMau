#ifndef CARD_H_
#define CARD_H_

#include <QString>

namespace Card {
  enum cardSuit {
    HEARTS = 1, DIAMONDS = 2, CLUBS = 3, SPADES = 4, NONE = 0
  };

  enum cardValue {
    SEVEN = 1,
    EIGHT = 2,
    NINE = 3,
    TEN = 4,
    JACK = 5,
    QUEEN = 6,
    KING = 7,
    ACE = 8,
    NONE = 0
  };
}


class Card {
private:
  cardSuit suit;
  cardValue value;
public:
  Card(cardSuit cSuit, cardValue cValue);
  cardSuit getSuit() const;
  cardValue getValue() const;
  QString as_string() const;
};


#endif /* CARD_H_ */
