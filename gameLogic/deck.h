#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include <algorithm>
#include <ctime>
#include <stdexcept>
#include "card.h"

/**
 * @brief The Deck class represents a card deck
 */
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
    /**
     * more information about the shuffle algorithm: http://bost.ocks.org/mike/shuffle/
     * @brief shuffle shuffles the deck with the Fished-Yates shuffle
     */
    void shuffle();
    void pushCard(const Card card);
    /**
     * returns the top card of the deck, if the deck is empty the underlying cards of the given deck are taken,
     * the deck is shuffled and the top card is returned. If this fails an exception is thrown.
     * @brief getLast returns the top card of the deck
     * @param deck the deck cards will be taken from if this deck is empty
     * @return the top card of the deck
     */
    Card getLast(Deck& deck);
    Card back() const;
    Card getCard(int index) const;
    /**
     * @brief addCards adds the given cards to the deck
     * @param newCards the cards to be added
     */
    void addCards(std::vector<Card> newCards);
    /**
     * returns all cards but the top/back card of this deck, all the returned cards are dropped afterwards.
     * @brief getUnderlyingCards returns all cards but the top/back card of this deck
     * @return all cards but the top/back card of this deck
     */
    std::vector<Card> getUnderlyingCards();
    bool empty() const;
};

#endif /* DECK_H_ */
