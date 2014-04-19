#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <sstream>



enum cardSuit {
	HEARTS = 0, DIAMONDS = 1, CLUBS = 2, SPADES = 3
};

enum cardValue {
	SEVEN = 1,
	EIGHT = 2,
	NINE = 3,
	TEN = 4,
	JACK = 5,
	QUEEN = 6,
	KING = 7,
	ACE = 8
};

class Card {
private:
	cardSuit suit;
	cardValue value;
public:
	Card(cardSuit cSuit, cardValue cValue);
	cardSuit getSuit() const;
	cardValue getValue() const;
//	string as_string() const;
	};

//ostream& operator<<(ostream& output, const Card& card);

#endif /* CARD_H_ */
