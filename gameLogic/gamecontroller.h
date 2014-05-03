#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QVector>
#include <QObject>
#include "deck.h"
#include "player.h"
#include "card.h"

class GameController : QObject {
    Q_OBJECT
private:
    QVector<Player> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;

    //flags
    int humanPlayer = 0;
    int currentPlayer = 0;
    bool changedDirection = false;
    bool colorWished = false;
    Card::cardSuit wishedSuit = Card::cardSuit(0);
    bool draw2x = false;
    int draw2xCount = 0;
    bool skipNextPlayer = false;
    //TODO always 4 players, 4+ players unregarded

public:
    explicit GameController(int currentPlayer = 0);

signals:
    void initPlayground(const QVector<Card>& humanPlayerCards, int* otherPlayerCardCount, const Card& topDepotCard, int startingPlayer);
    void playerDoTurn(QVector<Card>& playableCards); //an die view
    void playerPlaysCard(int player, const Card& playedCard);
    void playerDrawsCard(int player);
    //sends drawn card to the gui
    void addPlayerCard(const Card& card);

public
slots:
    void playCard(const Card& card);
    void drawCard();

private:
    void gameInit();
    void dealCards();
};

#endif // GAMECONTROLLER_H
