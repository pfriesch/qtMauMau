//============================================================================
// Name        : Aufgabe7
// Author      : Pius Friesch - s0540040
// Version     : 1.0
// Copyright   : none
// Description : Programm simulating a maumau game.
//============================================================================

#include <iostream>
#include <cstring>
#include "Maumau_game_holder.h"


bool check_parameters(int argc, char* argv[]);
void print_help();

int main(int argc, char* argv[]) {
	if (check_parameters(argc, argv)) {
		if (strcmp(argv[1], "-m") == 0) {
			Maumau_game_holder game_holder(true);
			game_holder.play();
		} else if (strcmp(argv[1], "-a") == 0) {
			Maumau_game_holder game_holder(false);
			game_holder.play();
		}
	} else {
		print_help();
	}
	return 0;
}

bool check_parameters(int argc, char* argv[]) {
	bool parameters_ok = false;
	if (argc == 2
			&& (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "-a") == 0)) {
		parameters_ok = true;
	}
	return parameters_ok;
}

void print_help() {
	cout << "maumau [option]" << endl
			<< "\t-m\tStarten eines Maumauspiels mit einem menschlichen Spieler."
			<< endl
			<< "\t-a\tStarten eins Maumauspiels, nur mit Computerspielern."
			<< endl;
}
