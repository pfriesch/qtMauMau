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
    vector<Player> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;

    //flags
    int playerCount;
    int humanPlayer = 0;
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

public:
    explicit GameController(int currentPlayer = 0, int playerCount = 4);
    void gameInit();

signals:
    /**
     * @brief initPlayground Sends signal to the View to initialize the playground
     * @param humanPlayerCards The cards of the human player
     * @param otherPlayerCardCount An array of integer with the card cound of the not human players [HEAP]
     * @param topDepotCard The top card of the Card Depot
     * @param startingPlayer The player who is the first to do his turn
     */
    void initPlayground(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer);
    /**
     * @brief playerDoTurn Sends a signal to the view with the cards the human player can play
     * @param playableCards
     */
    void playerDoTurn(vector<Card>& playableCards);
    /**
     * @brief playerPlaysCard Sends a signal to the view that the given non human player has played the given card
     * @param player the player who played a card
     * @param playedCard the card the non humanPlayer played
     */
    void playerPlaysCard(int player, const Card& playedCard);
    /**
     * @brief playerDrawsCard Sends a signal to the view that the given non humanPlayer has drawn a card
     * @param player the non human player who has drawn a card
     */
    void playerDrawsCard(int player);
    /**
     * @brief addPlayerCard Sends the expected drawn card of the humanPlayer to the view
     * @param card the drawn card
     */
    void addPlayerCard(const Card& card);

public
slots:
    /**
     * @brief playCard F
     * @param card
     */
    void playCard(const Card& card);
    void drawCard();
    void doNothing();

private:
    void dealCards();
    void nextTurn();
    void aiDoTurn(int aiPlayer);
    void setFlags(const Card& card);
    void setNextPlayer();
};

#endif // GAMECONTROLLER_H
