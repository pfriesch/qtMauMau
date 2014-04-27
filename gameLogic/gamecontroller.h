#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "deck.h"
#include "player.h"
#include "card.h"
#include "gstateflags.h"

class GameController {
private:
    QVector<Player> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;
    GStateFlags flags;

public:
    explicit GameController(short* currentPlayer = 0);
    void doTurn(Player& player);
    void playCard(Player& player, const Card& card);
    void drawCard(Player& player);
private:
    void gameInit();
    void dealCards(QVector<Player> &players);
};

#endif // GAMECONTROLLER_H
