#ifndef DECK_H_
#define DECK_H_

#include <QVector>
#include <algorithm>
#include <ctime>
#include <stdexcept>
#include "card.h"

class Deck {
private:
    QVector<Card> cards;

public:
    Deck(bool full_deck = false);
    void shuffle();
    void pushCard(const Card card);
    Card getLast(Deck& deck);
    Card back() const;

    Card getCard(int index) const;
    void addCards(QVector<Card>& newCards);
    QVector<Card>& getUnderlyingCards();
    bool empty() const;
    //TODO TEST
    int size() const;
};

#endif /* DECK_H_ */
