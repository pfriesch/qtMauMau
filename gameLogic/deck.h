#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include <algorithm>
#include <ctime>
#include <stdexcept>
#include "card.h"

class Deck {
#ifdef TEST
    friend class DeckTest;
#endif

public:
    enum InitStatus {
        FULL,
        EMPTY
    };

private:
    std::vector<Card> cards;

public:
    Deck(Deck::InitStatus staus = Deck::EMPTY);
    void shuffle();
    void pushCard(const Card card);
    Card getLast(Deck& deck);
    Card back() const;
    Card getCard(int index) const;
    void addCards(std::vector<Card> newCards);
    std::vector<Card> getUnderlyingCards();
    bool empty() const;
};

#endif /* DECK_H_ */
