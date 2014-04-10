#include "Maumau_game_holder.h"

Maumau_game_holder::Maumau_game_holder(bool is_human) :
		human_player(is_human), talon(Deck(true)), status_turn_before(
				STATUS_NONE), wished_suit(HEARTS), dropped_cards(Deck(false)) {
	talon.shuffle();
	players.push_back(Player(is_human));
	players.push_back(Player(false));
	players.push_back(Player(false));
	players.push_back(Player(false));
	deal_cards(players);
	dropped_cards.push_card(talon.get_last(dropped_cards));
	time_t t;
	time(&t);
	srand((unsigned int) t);
	player_on_move = players_names(rand() % 4);
	if (human_player) {
		output_game_situation_human(0);
	} else {
		output_game_situation_ai(0);
	}
}

bool Maumau_game_holder::play() {
	bool winner = false;
	unsigned int turn = 1;
	while (!winner) {
		press_any_key();
		cout << endl << endl << endl;
		winner = do_turn(player_on_move);
		if (human_player) {
			output_game_situation_human(turn);
		} else {
			output_game_situation_ai(turn);
		}
		if (winner) {
			cout << "Spieler " << player_on_move << " gewinnt!" << endl;
		}
		next_player();
		turn++;
	}
	return winner;
}

void Maumau_game_holder::deal_cards(vector<Player>& players) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			players[i].recive_card(talon.get_last(dropped_cards));
		}
	}
}

bool Maumau_game_holder::do_turn(players_names player) {
	if (status_turn_before == STATUS_DRAW_2
			|| status_turn_before == STATUS_DRAW_4
			|| status_turn_before == STATUS_DRAW_6
			|| status_turn_before == STATUS_DRAW_8) {
		if (players[player].has_seven()) {
			players[player].play_seven(dropped_cards);
			status_turn_before = game_status(status_turn_before + 2);
		} else {
			for (int i = 0; i < status_turn_before; i++) {
				players[player].recive_card(talon.get_last(dropped_cards));
			}
			if (play_single_card(players[player],
					dropped_cards.back().get_suit(), SEVEN)) {
				status_turn_before = STATUS_NONE;
			}
		}
	} else if (status_turn_before == STATUS_MISS_TURN) {
		status_turn_before = STATUS_NONE;
	} else if (status_turn_before == STATUS_WISHED_SUIT) {
		if (play_card(players[player], wished_suit, JACK)) {
			adjust_status();
		}
	} else {
		if (play_normal_card(players[player])) {
			adjust_status();
		}
	}
	bool winner = false;
	if (!players[player].has_cards()) {
		winner = true;
	}
	return winner;
}

bool Maumau_game_holder::play_single_card(Player& player,
		card_suit dropped_card_suit, card_value dropped_card_value) {
	bool played_card = false;
	if (player.can_play_card(dropped_card_suit, dropped_card_value)) {
		player.play_card(dropped_cards, dropped_card_suit, dropped_card_value);
		played_card = true;
	}
	return played_card;
}

bool Maumau_game_holder::play_card(Player& player, card_suit dropped_card_suit,
		card_value dropped_card_value) {
	bool played_card = false;
	if (play_single_card(player, dropped_card_suit, dropped_card_value)) {
		played_card = true;
	} else {
		player.recive_card(talon.get_last(dropped_cards));
		if (play_single_card(player, dropped_card_suit, dropped_card_value)) {
			played_card = true;
		}
	}
	return played_card;
}

bool Maumau_game_holder::play_normal_card(Player& player) {
	return play_card(player, dropped_cards.back().get_suit(),
			dropped_cards.back().get_value());
}

void Maumau_game_holder::draw_card(Player& player) {

}

void Maumau_game_holder::output_game_situation_ai(int turn) const {
	cout << "Spielsituation " << turn << endl << endl;
	for (unsigned int i = 0; i < players.size(); i++) {
		if (player_on_move == i) {
			cout << "Spieler " << i << ": X\t";
		} else {
			cout << "Spieler " << i << ":\t";
		}
	}
	cout << endl << endl;
	bool sb_has_cards = false;
	for (int i = 0; i < 32; i++) {
		for (unsigned int j = 0; j < players.size(); j++) {
			if (players[j].get_number_of_cards() <= i) {
				cout << "\t\t";
			} else {
				cout << players[j].get_card_at(i) << "\t";
				sb_has_cards = true;
			}
		}
		if (sb_has_cards) {
			cout << endl;
			sb_has_cards = false;
		} else
			i = 32;
	}
	cout << endl << endl;
	for (unsigned int j = 0; j < players.size(); j++) {
		cout << "--------------- ";
	}
	cout << endl << endl << "abgelegte Karten:\t\tTalon:" << endl << endl;
	for (int i = 0; i < 32; i++) {
		if (i < dropped_cards.size()) {
			cout << dropped_cards.get_card(i) << "\t\t\t";
		} else {
			cout << "\t\t\t\t";
		}
		if (i < talon.size()) {
			cout << talon.get_card(i) << endl;
		} else {
			cout << endl;
		}
		if (i > dropped_cards.size() && i > talon.size()) {
			i = 32;
		}
	}
	cout << endl;
	for (unsigned int j = 0; j < players.size(); j++) {
		cout << "--------------- ";
	}
	cout << endl;
}

void Maumau_game_holder::output_game_situation_human(int turn) const {
	cout << "Spielsituation " << turn << endl << endl;
	for (unsigned int i = 0; i < players.size(); i++) {
		if (player_on_move == i) {
			cout << "Spieler " << i << ": X\t";
		} else {
			cout << "Spieler " << i << ":\t";
		}
	}
	cout << endl << endl;
	for (int i = 0; i < players[0].get_number_of_cards(); i++) {
		cout << players[0].get_card_at(i) << "\t";
		if (i == 0)
			for (unsigned int j = 1; j < players.size(); j++)
				cout << "hat " << players[j].get_number_of_cards()
						<< " Karten\t";
		cout << endl;
	}
	cout << endl << endl;
	for (unsigned int j = 0; j < players.size(); j++) {
		cout << "--------------- ";
	}
	cout << endl << endl << "abgelegte Karten:\t\tTalon:" << endl << endl;
	cout << dropped_cards.back() << "\t\t\that " << talon.size() << " Karten"
			<< endl << "und " << dropped_cards.size() - 1 << " weitere" << endl;
	cout << endl;
	for (unsigned int j = 0; j < players.size(); j++) {
		cout << "--------------- ";
	}
	cout << endl;
}

void Maumau_game_holder::next_player() {
	if (player_on_move < 3) {
		player_on_move = players_names(player_on_move + 1);
	} else {
		player_on_move = players_names(0);
	}
}

void Maumau_game_holder::adjust_status() {
	Card latest_played_card(dropped_cards.back());
	switch (latest_played_card.get_value()) {
	case SEVEN:
		status_turn_before = STATUS_DRAW_2;
		break;
	case ACE:
		status_turn_before = STATUS_MISS_TURN;
		break;
	case JACK:
		status_turn_before = STATUS_WISHED_SUIT;
		wished_suit = players[player_on_move].get_wished_suit();
		break;
	default:
		status_turn_before = STATUS_NONE;
		break;
	}
}

