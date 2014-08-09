#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdexcept>
#include <vector>
#include "deck.h"

#include "player.h"
#include "PlayerName.h"
#include "card.h"

class GameController {

private:
    std::vector<Player*> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;

    //player at 0 is always the current player
    std::vector<PLAYER::Name> playerOrder;

    bool changedDirection = false;
    Card::cardSuit wishedSuit = Card::cardSuit(0);
    bool draw2x = false;
    int draw2xCount = 0;
    bool skipNextPlayer = false;
    //TODO always 4 players, 4+ players unregarded

    //special cards

    const Card::cardValue draw2xCard = Card::SEVEN;

    const Card::cardValue wishSuitCard = Card::JACK;

    const Card::cardValue skipNextCard = Card::EIGHT;

    const Card::cardValue changeDirectCard = Card::TEN;

public:
    explicit GameController();
    void localGame(int playerCount = 4);
    void networkGame(std::vector<Player*> remotePlayers);
    void gameInit();
    void playCard(PLAYER::Name pName, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(PLAYER::Name pName);

    Player* getBottomPlayer();

private:
    void nextTurn();
    void setFlags(const Card& card);
    void setNextPlayer();
    void playerDrawCard(PLAYER::Name pName);
    void handleDraw2x();
};

#endif // GAMECONTROLLER_H
