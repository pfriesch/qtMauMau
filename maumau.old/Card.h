#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <sstream>



enum card_suit {
	HEARTS = 0, DIAMONDS = 1, CLUBS = 2, SPADES = 3
};

enum card_value {
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
	card_suit suit;
	card_value value;
public:
	Card(card_suit c_suit, card_value c_value);
	card_suit get_suit() const;
	card_value get_value() const;
	string as_string() const;
	};

ostream& operator<<(ostream& output, const Card& card);

#endif /* CARD_H_ */
