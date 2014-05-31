#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <stdexcept>
#include "deck.h"
#include "player.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include "card.h"

#include <QDebug>

class GameController : public QObject {
    Q_OBJECT
private:
    vector<Player*> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;

    //flags
    int playerCount;
    //default start player is 0

    //every turn flags
    int currentPlayer;
    bool changedDirection = false;
    bool colorWished = false;
    Card::cardSuit wishedSuit = Card::cardSuit(0);
    bool draw2x = false;
    int draw2xCount = 0;
    bool skipNextPlayer = false;
    //TODO always 4 players, 4+ players unregarded
    bool currentPlayerDrewCard = false;
    bool currentPlayerPlayedCard = false;

    //special cards
    bool withDraw2xCard = true;
    const Card::cardValue draw2xCard = Card::SEVEN;
    bool withWishedSuit = true;
    const Card::cardValue wishSuitCard = Card::JACK;
    bool withSkipPlayer = true;
    const Card::cardValue skipNextCard = Card::EIGHT;
    bool withChangeDirection = false;
    const Card::cardValue changeDirectCard = Card::TEN;

public
slots:
    void playCard(int playerId, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(int playerId);
    void doNothing(int playerId);

signals:
    void playerPlaysCard(int playerId, const Card& playedCard);
    void playerDrawsCard(int playerId);

public:
    explicit GameController(int currentPlayer = 0, int playerCount = 4);
    void gameInit();

private:
    void connectPlayerSignals();
    void nextTurn();
    void setFlags(const Card& card);
    void setNextPlayer();
};

#endif // GAMECONTROLLER_H
