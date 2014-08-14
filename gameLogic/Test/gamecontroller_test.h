#ifdef TEST
#ifndef GAMECONTROLLERTEST_H
#define GAMECONTROLLERTEST_H

#include <QObject>
#include <QtTest/QTest>
#include "gameLogic/gamecontroller.h"
#include "gameLogic/aiplayer.h"
#include "gameLogic/Test/gcproxy_mockup.h"

class GameControllerTest : public QObject {
    Q_OBJECT
private:
    GameController gc;

private
slots:
    void init()
    {
        gc = GameController();
        GCProxy_mockup gcp;
        AIPlayer* p1 = new AIPlayer(PLAYER::NONE, gcp, "test");
        AIPlayer* p2 = new AIPlayer(PLAYER::NONE, gcp, "test");
        std::vector<Player*> player;
        player.push_back(p1);
        player.push_back(p2);
        gc.setPlayers(player);

        gc.draw2xCard = Card::SEVEN;
        gc.wishSuitCard = Card::JACK;
        gc.skipNextCard = Card::EIGHT;
        gc.changeDirectCard = Card::TEN;
    }

    void handleDraw2xTest()
    {

        gc.draw2x = true;
        gc.draw2xCount = 2;
        gc.handleDraw2x();
        QVERIFY(gc.players.at(0)->getCardCount() == 2);
    }
    void setFlagsTest1()
    {
        Card card = Card(Card::HEARTS, Card::ACE);
        gc.setFlags(card);

        QVERIFY(!gc.changedDirection);
        QVERIFY(!gc.draw2x);
        QVERIFY(!gc.skipNextPlayer);
        QVERIFY(gc.wishedSuit == Card::NONE);
        QVERIFY(gc.draw2xCount == 0);
    }

    void setFlagsTest2()
    {
        Card card = Card(Card::HEARTS, Card::EIGHT);
        gc.setFlags(card);

        QVERIFY(!gc.changedDirection);
        QVERIFY(!gc.draw2x);
        QVERIFY(gc.skipNextPlayer);
        QVERIFY(gc.wishedSuit == Card::NONE);
        QVERIFY(gc.draw2xCount == 0);
    }
    void setFlagsTest3()
    {
        Card card = Card(Card::HEARTS, Card::TEN);
        gc.setFlags(card);

        QVERIFY(gc.changedDirection);
        QVERIFY(!gc.draw2x);
        QVERIFY(!gc.skipNextPlayer);
        QVERIFY(gc.wishedSuit == Card::NONE);
        QVERIFY(gc.draw2xCount == 0);
    }

    void cleanp()
    {
        delete gc.players.at(0);
        delete gc.players.at(1);
    }
};

#endif // GAMECONTROLLERTEST_H
#endif //TEST
