#include "card.h"

Card::Card(const cardSuit cSuit, const cardValue cValue) :
		suit(cSuit), value(cValue) {
}

cardSuit Card::getSuit() const {
	return suit;
}

cardValue Card::getValue() const {
	return value;
}

bool Card::operator ==(const Card &card) const{
  return ((card.getSuit()==suit))&&(card.getValue()==value);
}


//ostream& operator<<(ostream& output, const Card& card) {
//	output << card.as_string();
//	return output;
//}

//string Card::as_string() const {
//	stringstream string_stream;
//	switch (suit) {
//	case HEARTS:
//		string_stream << "Herz  ";
//		break;
//	case DIAMONDS:
//		string_stream << "Karo  ";
//		break;
//	case CLUBS:
//		string_stream << "Kreuz ";
//		break;
//	case SPADES:
//		string_stream << "Pik   ";
//		break;
//	}
//	switch (value) {
//	case SEVEN:
//		string_stream << "Sieben";
//		break;
//	case EIGHT:
//		string_stream << "Acht  ";
//		break;
//	case NINE:
//		string_stream << "Neun  ";
//		break;
//	case TEN:
//		string_stream << "Zehn  ";
//		break;
//	case JACK:
//		string_stream << "Bube  ";
//		break;
//	case QUEEN:
//		string_stream << "Dame  ";
//		break;
//	case KING:
//		string_stream << "König ";
//		break;
//	case ACE:
//		string_stream << "Ass   ";
//		break;
//	}
//	return string_stream.str();
//}
