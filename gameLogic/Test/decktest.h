#ifndef DECKTEST_H
#define DECKTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <stdexcept>
#include <exception>
#include "gameLogic/deck.h"
#ifdef TEST

class DeckTest : public QObject {
    Q_OBJECT
private:
private
slots:

    void shuffleTest()
    {
        Deck fullDeck = Deck(Deck::FULL);
        Card card = fullDeck.back();
        Card card2 = fullDeck.getCard(4);
        fullDeck.shuffle();
        QVERIFY(!(card == fullDeck.back()));
        QVERIFY(!(card2 == fullDeck.getCard(4)));
    }
    void getLastTest()
    {
        try
        {
            Deck fullDeck = Deck(Deck::FULL);
            Deck fullDeck2 = Deck(Deck::FULL);
            Card card = fullDeck.getLast(fullDeck2);
            QVERIFY(!(card == fullDeck.getLast(fullDeck2)));
        }
        catch (std::exception e)
        {
            QFAIL(e.what());
        }
        try
        {
            Deck emptyDeck = Deck(Deck::EMPTY);
            Deck fullDeck2 = Deck(Deck::FULL);
            Card card = fullDeck2.getCard(fullDeck2.cards.size() - 1);
            Card card2 = emptyDeck.getLast(fullDeck2);
            QVERIFY(!(card == card2));
        }
        catch (std::exception e)
        {
            QFAIL(e.what());
        }
        try
        {
            Deck emptyDeck = Deck(Deck::EMPTY);
            Deck emptyDeck2 = Deck(Deck::EMPTY);
            emptyDeck.getLast(emptyDeck2);
        }
        catch (std::exception e)
        {
            QVERIFY(true);
        }
    }
    void getUnderlyingCardsTest()
    {
        Deck fulldeck = Deck(Deck::FULL);
        Deck emptyDeck = Deck(Deck::EMPTY);
    }
};

#endif
#endif // DECKTEST_H
