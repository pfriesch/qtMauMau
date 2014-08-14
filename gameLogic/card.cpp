#include "card.h"

Card::Card(const cardSuit cSuit, const cardValue cValue)
    : suit(cSuit)
    , value(cValue)
{
}

Card::Card(const Card& card)
    : suit(card.getSuit())
    , value(card.getValue())
{
}

Card::Card()
    : suit(Card::cardSuit(1))
    , value(Card::cardValue(1))
{
}

Card::cardSuit Card::getSuit() const
{
    return suit;
}

Card::cardValue Card::getValue() const
{
    return value;
}

bool Card::operator==(const Card& card) const
{
    return ((card.getSuit() == suit)) && (card.getValue() == value);
}
