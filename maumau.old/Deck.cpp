#include "Deck.h"

/**
 * Initializes a full cad deck
 */
Deck::Deck(bool full_deck) {
	if (full_deck) {
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= 8; j++) {
				cards.push_back(Card(card_suit(i), card_value(j)));
			}
		}
	}
}
void Deck::shuffle() {
	time_t t;
	time(&t);
	srand((unsigned int) t);
	random_shuffle(cards.begin(), cards.end());
}

int Deck::size() const {
	return cards.size();
}

void Deck::push_card(const Card card) {
	cards.push_back(card);
}

const Card Deck::get_last(Deck& dropped_cards) {
	if (this->empty()) {
		this->add_cards(dropped_cards.get_underlying_cards());
	}
	Card returned_card = cards.back();
	cards.pop_back();
	return returned_card;
}

const Card Deck::back() const {
	return cards.back();
}

bool Deck::empty() const {
	return cards.empty();
}
const Card Deck::get_card(int index) const {
	return cards[index];
}

vector<Card> Deck::get_underlying_cards() {
	vector<Card> underlying_cards = cards;
	underlying_cards.pop_back();
	cards.erase(cards.begin(), cards.end() - 1);
	return underlying_cards;
}

void Deck::add_cards(vector<Card> new_cards) {
	cards.insert(cards.end(), new_cards.begin(), new_cards.end());
	shuffle();
}
