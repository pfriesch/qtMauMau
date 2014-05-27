#include "deck.h"

/**
 * Initializes a full cad deck
 */
Deck::Deck(Deck::InitStatus status)
{
    if (status == Deck::f) {
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
    int m = cards.size();
    Card temp;
    int i;
    while (m) {
        i = (rand() % m--);
        temp = cards[m];
        cards[m] = cards[i];
        cards[i] = temp;
    }
}
#ifdef TEST
int Deck::size() const
{
    return cards.size();
}
#endif

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
Card Deck::getLast(Deck& cardDepot)
{
    if (empty()) {
        if (cardDepot.empty()) {
            throw std::invalid_argument("cardDepot contains too few cards");
        } else {
            addCards(cardDepot.getUnderlyingCards());
        }
    }
    Card returned_card = cards.back();
    cards.pop_back();
    return returned_card;
}

Card Deck::back() const
{
    return cards.back();
}

bool Deck::empty() const
{
    return cards.empty();
}
Card Deck::getCard(int index) const
{
    return cards.at(index);
}

vector<Card>& Deck::getUnderlyingCards()
{
    vector<Card>* underlyingCards = new vector<Card>;
    *underlyingCards = cards;
    underlyingCards->pop_back();
    cards.erase(cards.begin(), cards.end() - 1);
    return *underlyingCards;
}

void Deck::addCards(vector<Card>& newCards)
{
    cards.insert(cards.end(), newCards.begin(), newCards.end());
    shuffle();
}
