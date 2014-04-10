#include "Card.h"

Card::Card(const card_suit c_suit, const card_value c_value) :
		suit(c_suit), value(c_value) {
}

card_suit Card::get_suit() const {
	return suit;
}

card_value Card::get_value() const {
	return value;
}

ostream& operator<<(ostream& output, const Card& card) {
	output << card.as_string();
	return output;
}

string Card::as_string() const {
	stringstream string_stream;
	switch (suit) {
	case HEARTS:
		string_stream << "Herz  ";
		break;
	case DIAMONDS:
		string_stream << "Karo  ";
		break;
	case CLUBS:
		string_stream << "Kreuz ";
		break;
	case SPADES:
		string_stream << "Pik   ";
		break;
	}
	switch (value) {
	case SEVEN:
		string_stream << "Sieben";
		break;
	case EIGHT:
		string_stream << "Acht  ";
		break;
	case NINE:
		string_stream << "Neun  ";
		break;
	case TEN:
		string_stream << "Zehn  ";
		break;
	case JACK:
		string_stream << "Bube  ";
		break;
	case QUEEN:
		string_stream << "Dame  ";
		break;
	case KING:
		string_stream << "König ";
		break;
	case ACE:
		string_stream << "Ass   ";
		break;
	}
	return string_stream.str();
}
