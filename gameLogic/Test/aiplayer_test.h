#ifdef TEST
#ifndef AIPLAYER_TEST_H
#define AIPLAYER_TEST_H

#include <QObject>
#include <QTest>

#include "gameLogic/aiplayer.h"
#include "gameLogic/Test/gcproxy_mockup.h"

class AIPlayer_test : public QObject {

    Q_OBJECT
private:
private
slots:

    void testGetPlayableCards()
    {
        GCProxy_mockup gc;
        AIPlayer* player = new AIPlayer(PLAYER::NONE, gc, "test");
        player->wishSuitCard = Card::JACK;
        player->hand.push_back(Card(Card::HEARTS, Card::ACE));
        player->hand.push_back(Card(Card::HEARTS, Card::KING));
        player->hand.push_back(Card(Card::HEARTS, Card::EIGHT));
        player->hand.push_back(Card(Card::SPADES, Card::ACE));
        player->hand.push_back(Card(Card::SPADES, Card::KING));
        Card topCard = Card(Card::HEARTS, Card::ACE);
        std::vector<Card> playableCards = player->getPlayableCards(topCard, Card::NONE);
        for (unsigned i = 0; i < playableCards.size(); ++i) {
            QVERIFY(playableCards.at(i) == player->hand.at(i));
        }
        delete player;

        player = new AIPlayer(PLAYER::NONE, gc, "test");
        player->wishSuitCard = Card::JACK;
        player->hand.push_back(Card(Card::SPADES, Card::ACE));
        player->hand.push_back(Card(Card::HEARTS, Card::KING));
        player->hand.push_back(Card(Card::HEARTS, Card::JACK));
        player->hand.push_back(Card(Card::SPADES, Card::ACE));
        player->hand.push_back(Card(Card::SPADES, Card::KING));
        topCard = Card(Card::SPADES, Card::ACE);
        playableCards = player->getPlayableCards(topCard, Card::NONE);
        for (unsigned i = 0; i < playableCards.size(); ++i) {
            QVERIFY((playableCards.at(i).getSuit() == Card::SPADES) || (playableCards.at(i).getValue() == Card::JACK));
        }
        delete player;
    }
    void wishedCardTest()
    {
        GCProxy_mockup gc;
        AIPlayer* player = new AIPlayer(PLAYER::NONE, gc, "test");
        std::vector<Card> hand;
        hand.push_back(Card(Card::HEARTS, Card::ACE));
        hand.push_back(Card(Card::HEARTS, Card::KING));
        hand.push_back(Card(Card::HEARTS, Card::EIGHT));
        hand.push_back(Card(Card::SPADES, Card::ACE));
        hand.push_back(Card(Card::SPADES, Card::KING));
        player->hand = hand;
        player->wishSuitCard = Card::JACK;
        QVERIFY(Card::HEARTS == player->getWhishedCardSuit());
        delete player;
    }
};

#endif // AIPLAYER_TEST_H
#endif //TEST
