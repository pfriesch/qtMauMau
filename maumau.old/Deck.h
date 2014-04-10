#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include <algorithm>
#include "Card.h"

class Deck {
private:
	vector<Card> cards;
public:
	Deck(bool full_deck);
	void shuffle();
	void push_card(const Card card);
	const Card get_last(Deck& deck);
	const Card back() const;
	int size() const;
	bool empty() const;
	const Card get_card(int index) const;
	void add_cards(vector<Card> new_cards);
	vector<Card> get_underlying_cards();
};

#endif /* DECK_H_ */
