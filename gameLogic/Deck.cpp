#include "deck.h"

/**
 * Initializes a full cad deck
 */
Deck::Deck(bool full_deck)
{
    if (full_deck) {
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j <= 8; j++) {
                cards.push_back(Card(Card::cardSuit(i), Card::cardValue(j)));
            }
        }
    }
    this->shuffle();
}

/*
 * http://bost.ocks.org/mike/shuffle/
 *
 */
void Deck::shuffle()
{


//    std::random_shuffle(cards.begin(), cards.end());
  int m = cards.length();
  Card temp;
  int i;
  while (m) {
      i = (rand() * m--);
      temp = cards[m];
      cards[m] = cards[i];
      cards[i] = temp;

    }

}

//int Deck::size() const {
//  return cards.size();
//}

void Deck::pushCard(const Card card)
{
    cards.push_back(card);
}

/**
 * Returns the last card of the deck, if this deck is empty
 * the Deck is refilled by the underlying cards of the given deck,
 * shuffled and then the last card is returned.
 * @brief Returns the last card of the deck.
 * @param dropped_cards
 * @return
 */
const Card Deck::getLast(Deck& dropped_cards)
{
    if (empty()) {
        addCards(dropped_cards.getUnderlyingCards());
    }
    Card returned_card = cards.back();
    cards.pop_back();
    return returned_card;
}

const Card Deck::back() const
{
    return cards.back();
}

bool Deck::empty() const
{
    return cards.empty();
}
const Card Deck::getCard(int index) const
{
    return cards.at(index);
}

QVector<Card>& Deck::getUnderlyingCards()
{
    QVector<Card>* underlying_cards = new QVector<Card>;
    *underlying_cards << cards;
    underlying_cards->pop_back();
    cards.erase(cards.begin(), cards.end() - 1);
    return *underlying_cards;
}

void Deck::addCards(QVector<Card>& newCards)
{
    cards << newCards;

    shuffle();
}
