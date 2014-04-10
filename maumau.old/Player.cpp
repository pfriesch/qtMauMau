#include "Player.h"
#include "console_input.h"

Player::Player(bool is_human) :
		human(is_human) {
}

void Player::recive_card(Card card) {
	if (human) {
		cout << "Ziehe Karte: " << card << endl;
	}
	hand.push_back(card);
}

int Player::get_number_of_cards() const {
	return hand.size();
}

const Card Player::get_card_at(int index) const {
	return hand[index];
}

bool Player::can_play_card(card_suit dropped_card_suit,
		card_value dropped_card_value) const {
	bool can_play_card = false;
	if (!human) {
		can_play_card = can_play_card_ai(dropped_card_suit, dropped_card_value);
	} else {
		can_play_card = can_play_card_human(dropped_card_suit,
				dropped_card_value);
	}
	return can_play_card;
}

void Player::play_card(Deck& dropped_cards, card_suit dropped_card_suit,
		card_value dropped_card_value) {
	if (human) {
		play_card_human(dropped_cards, dropped_card_suit, dropped_card_value);
	} else {
		play_card_ai(dropped_cards, dropped_card_suit, dropped_card_value);
	}

}

bool Player::has_seven() const {
	bool has_seven = false;
	if (!human) {
		has_seven = has_seven_ai();
	} else {
		has_seven = has_seven_human();
	}
	return has_seven;
}

void Player::play_seven(Deck& dropped_cards) {
	if (human) {
		play_seven_human(dropped_cards);
	} else {
		play_seven_ai(dropped_cards);
	}
}

bool Player::has_cards() const {
	return !hand.empty();
}

card_suit Player::get_wished_suit() {
	card_suit wished_suit = card_suit(0);
	if (human) {
		vector<string> suits;
		suits.push_back("Herz");
		suits.push_back("Karo");
		suits.push_back("Kreuz");
		suits.push_back("Pik");
		wished_suit = card_suit(
				request_menu(suits, 4,
						"Bitte waehlen sie die gewuenschte Farbe."));
	} else {
		int suits[4] = { 0, 0, 0, 0 };
		for (unsigned int i = 0; i < hand.size(); i++) {
			if (hand[i].get_value() != JACK) {
				suits[hand[i].get_suit()]++;
			}
		}
		int current_index = 0;
		int current_max = suits[0];
		for (int i = 0; i < 4; i++) {
			if (suits[i] > current_max) {
				current_max = suits[i];
				current_index = i;
			}
		}
		wished_suit = card_suit(current_index);
	}
	cout << "Die gewünschte Farbe ist: ";
	switch (wished_suit) {
	case HEARTS:
		cout << "Herz";
		break;
	case SPADES:
		cout << "Pik";
		break;
	case CLUBS:
		cout << "Kreuz";
		break;
	case DIAMONDS:
		cout << "Karo";
		break;
	}
	cout << endl;
	return wished_suit;
}

bool Player::can_play_card_ai(card_suit dropped_card_suit,
		card_value dropped_card_value) const {
	bool can_play_card = false;
	for (unsigned int i = 0; i < hand.size() && !can_play_card; i++) {
		if (hand[i].get_suit() == dropped_card_suit
				|| hand[i].get_value() == dropped_card_value
				|| hand[i].get_value() == JACK) {
			can_play_card = true;
		}
	}
	return can_play_card;
}
bool Player::can_play_card_human(card_suit dropped_card_suit,
		card_value dropped_card_value) const {
	bool can_play_card = false;
	vector<Card> possible_cards;
	for (unsigned int i = 0; i < hand.size() && !can_play_card; i++) {
		if (hand[i].get_suit() == dropped_card_suit
				|| hand[i].get_value() == dropped_card_value
				|| hand[i].get_value() == JACK) {
			possible_cards.push_back(hand[i]);
		}
	}
	if (possible_cards.size() > 0) {
		cout << "Diese Karten können gespielt werden." << endl;
		for (unsigned int i = 0; i < possible_cards.size(); ++i) {
			cout << possible_cards[i] << endl;
		}
		const char *options[] = { "Ja", "Nein" };
		if (request_menu(vector<string>(options, options + 2), 2,
				"Möchten sie eine Karte spielen?") == 0) {
			can_play_card = true;
		}
	}
	return can_play_card;
}

void Player::play_card_ai(Deck& dropped_cards, card_suit dropped_card_suit,
		card_value dropped_card_value) {
	bool played_card = false;
	for (unsigned int i = 0; i < hand.size() && !played_card; i++) {
		if (hand[i].get_value() == dropped_card_value
				|| hand[i].get_suit() == dropped_card_suit
				|| hand[i].get_value() == JACK) {
			dropped_cards.push_card(hand[i]);
			hand.erase(hand.begin() + i);
			played_card = true;
		}
	}
}

void Player::play_card_human(Deck& dropped_cards, card_suit dropped_card_suit,
		card_value dropped_card_value) {
	vector<int> playable_cards_i;
	vector<Card> playable_cards;
	for (unsigned int i = 0; i < hand.size(); i++) {
		if (hand[i].get_suit() == dropped_card_suit
				|| hand[i].get_value() == dropped_card_value
				|| hand[i].get_value() == JACK) {
			playable_cards_i.push_back(i);
			playable_cards.push_back(hand[i]);
		}
	}
	if (playable_cards.size() > 1) {
		int whished_card_i = get_wished_card(playable_cards);
		dropped_cards.push_card(playable_cards[whished_card_i]);
		hand.erase(hand.begin() + playable_cards_i[whished_card_i]);
	} else {
		dropped_cards.push_card(playable_cards[0]);
		hand.erase(hand.begin() + playable_cards_i[0]);
	}
}

bool Player::has_seven_ai() const {
	bool seven = false;
	for (unsigned int i = 0; i < hand.size() && !seven; i++) {
		if (hand[i].get_value() == SEVEN) {
			seven = true;
		}
	}
	return seven;
}
void Player::play_seven_ai(Deck& dropped_cards) {
	bool played_seven = false;
	for (unsigned int i = 0; i < hand.size() && !played_seven; i++) {
		if (hand[i].get_value() == SEVEN) {
			dropped_cards.push_card(hand[i]);
			hand.erase(hand.begin() + i);
			played_seven = true;
		}
	}
}
bool Player::has_seven_human() const {
	bool seven = false;
	for (unsigned int i = 0; i < hand.size() && !seven; i++) {
		if (hand[i].get_value() == SEVEN) {
			const char *options[] = { "Ja", "Nein" };
			if (request_menu(vector<string>(options, options + 2), 2,
					"Möchten sie eine Sieben spielen?") == 0) {
				seven = true;
			}
		}
	}
	return seven;
}

void Player::play_seven_human(Deck& dropped_cards) {
	vector<int> playable_cards_i;
	vector<Card> playable_cards;
	for (unsigned int i = 0; i < hand.size(); i++) {
		if (hand[i].get_value() == SEVEN) {
			playable_cards_i.push_back(i);
			playable_cards.push_back(hand[i]);
		}
	}
	if (playable_cards.size() > 1) {
		int whished_card_i = get_wished_card(playable_cards);
		dropped_cards.push_card(playable_cards[whished_card_i]);
		hand.erase(hand.begin() + playable_cards_i[whished_card_i]);
	} else {
		dropped_cards.push_card(playable_cards[0]);
		hand.erase(hand.begin() + playable_cards_i[0]);
	}
}

int Player::get_wished_card(const vector<Card> playable_cards) {
	vector<string> playable_cards_string;
	for (unsigned int i = 0; i < playable_cards.size(); ++i) {
		playable_cards_string.push_back(playable_cards[i].as_string());
	}
	int chosen_card = request_menu(playable_cards_string, playable_cards.size(),
			"Bitte waehlen sie die zu spielende Karte.");
	return chosen_card;
}

