#ifndef MAUMAU_GAME_H_
#define MAUMAU_GAME_HOLDER_H_

#include <vector>
#include <cstdlib>
#include <time.h>

#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "game_status.h"
#include "console_input.h"

enum players_names {
	PLAYER_1 = 0, PLAYER_2 = 1, PLAYER_3 = 2, PLAYER_4 = 3
};

class Maumau_game_holder {
private:
	vector<Player> players;
	bool human_player;
	Deck talon;
	players_names player_on_move;
	game_status status_turn_before;
	card_suit wished_suit;
	Deck dropped_cards;
public:
	Maumau_game_holder(bool is_human);
	bool play();
private:
	bool play_single_card(Player& player, card_suit dropped_card_suit,
			card_value dropped_card_value);
	bool play_normal_card(Player& player);
	bool play_card(Player& player, card_suit dropped_card_suit,
			card_value dropped_card_value);
	void draw_card(Player& player);
	void output_game_situation_ai(int turn) const;
	void output_game_situation_human(int turn) const;
	bool do_turn(players_names player);
	void deal_cards(vector<Player>& players);
	void next_player();
	void adjust_status();
};

#endif /* MAUMAU_GAME_H_ */
