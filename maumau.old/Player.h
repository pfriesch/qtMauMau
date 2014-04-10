#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "Card.h"
#include "Deck.h"
#include "game_status.h"

class Player {
private:
	bool human;
	vector<Card> hand;
public:
	Player(bool is_human);
	int get_number_of_cards() const;
	const Card get_card_at(int index) const;
	void recive_card(Card card);
	bool can_play_card(card_suit dropped_card_suit,
			card_value dropped_card_value) const;
	void play_card(Deck& dropped_cards, card_suit dropped_card_suit,
			card_value dropped_card_value);
	bool has_seven() const;
	void play_seven(Deck& dropped_cards);
	bool has_cards() const;
	card_suit get_wished_suit();
private:
	bool can_play_card_ai(card_suit dropped_card_suit,
			card_value dropped_card_value) const;
	bool can_play_card_human(card_suit dropped_card_suit,
			card_value dropped_card_value) const;
	void play_card_ai(Deck& dropped_cards, card_suit dropped_card_suit,
			card_value dropped_card_value);
	void play_card_human(Deck& dropped_cards, card_suit dropped_card_suit,
			card_value dropped_card_value);
	bool has_seven_ai() const;
	void play_seven_ai(Deck& dropped_cards);
	bool has_seven_human() const;
	void play_seven_human(Deck& dropped_cards);
	int get_wished_card(const vector<Card> playable_cards);
};

#endif /* PLAYER_H_ */
