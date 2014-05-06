#ifndef DECKTEST_H
#define DECKTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <stdexcept>
#include <exception>
#include "gameLogic/Deck.h"

class DeckTest : public QObject {
    Q_OBJECT
private:
    Deck fullDeck;
    Deck backupDeck;
    Deck emptyDeck;
private
slots:
    void initTestCase()

    {
        fullDeck = Deck(true);
        backupDeck = Deck(true);
        emptyDeck = Deck();
    }
    void myFirstTest()
    {
        try
        {
            for (int i = 0; i < fullDeck.size() + 5; ++i) {

                fullDeck.getLast(emptyDeck);
            }
        }
        catch (std::exception& e)
        {
        qDebug("blub");
            QFAIL(e.what());
        }
    }
    void mySecondTest()
    {
        QVERIFY(1 != 2);
    }
    void cleanupTestCase()
    {
        qDebug("called after myFirstTest and mySecondTest");
    }
};

#endif // DECKTEST_H
