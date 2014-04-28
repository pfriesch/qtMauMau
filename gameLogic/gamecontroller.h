#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QVector>
#include <QObject>
#include "deck.h"
#include "player.h"
#include "card.h"
#include "gstateflags.h"

class GameController : QObject {
    Q_OBJECT
private:
    QVector<Player> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;
    GStateFlags flags;

public:
    explicit GameController(short* currentPlayer = 0);

signals:
    void initPlayground(QVector<Cards>* humanPlayerCards, QVecotr<Short> otherPlayerCardCount, const Card& topDepotCard, short startingPlayer);
    void playerDoTurn(QVector<Card>* playableCards); //an die view
    void playerPlaysCard(short player, const Card& playedCard);
    void playerDrawsCard(short player);
    //sends drawn card to the gui
    void addPlayerCard(const Card& card);

public
slots:
    void playCard(const Card& card);
    void drawCard();

private:
    void gameInit();
    void dealCards(QVector<Player>& players);
};

#endif // GAMECONTROLLER_H
