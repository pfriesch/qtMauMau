#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdexcept>
#include <vector>
#include "deck.h"

#include "player.h"
#include "playername.h"
#include "card.h"

/**
 * he GameController class handle the logic of the maumau game. The current state of the game is saved here.
 * For every game a new Gamecontroller is createt. Players are set after. These Players have to implement the Player abstract Class.
 * There are two card decks, the first, the card Stack holds all unused cards, which are ready to be drawn.
 *
 * @brief The GameController class handle the logic of the maumau game
 */
class GameController {
#ifdef TEST
    friend class GameControllerTest;
#endif
private:
    std::vector<Player*> players;
    /**
     * @brief cardStack the cards where players draw from
     */
    Deck cardStack;
    /**
     * @brief cardDepot all played cards are droped here
     */
    Deck cardDepot;

    /**
     * playerOrder the player at the index 0 is the current player, the vector is rotated after each round
     * @brief playerOrder the player at the index 0 is the current player
     */
    std::vector<PLAYER::Name> playerOrder;

    /**
     * @brief playerPlayed guard so a player can not play two cards
     */
    bool playerPlayed = false;
    /**
     * @brief aPlayerWon set true when a player won
     */
    bool aPlayerWon = false;

    bool changedDirection = false;
    Card::cardSuit wishedSuit = Card::NONE;
    bool draw2x = false;
    int draw2xCount = 0;
    bool skipNextPlayer = false;

    //special cards
    Card::cardValue draw2xCard;
    Card::cardValue wishSuitCard;
    Card::cardValue skipNextCard;
    Card::cardValue changeDirectCard;

public:
    /**
     * @brief GameController initialized with a full cardStack
     */
    explicit GameController();
    ~GameController();
    /**
     * @brief setPlayers sets the given players to the gamecontroller players
     * @param _players all the players used by the gamecontroller
     */
    void setPlayers(std::vector<Player*> _players);
    /**
     * Initializes the card stacks and card depot and distributes cards to the players.
     * Initialzes players with thier cards usw.
     * Calls do turn on the current player.
     * @brief gameInit initializes a game
     * @param _draw2xCard custom draw 2 cards card
     * @param _wishSuitCard custom wish suit card
     * @param _skipNextCard custom card to skip the next player
     * @param _changeDirectCard custom card to change the direction
     */
    void gameInit(Card::cardValue _draw2xCard = Card::SEVEN,
                  Card::cardValue _wishSuitCard = Card::JACK,
                  Card::cardValue _skipNextCard = Card::EIGHT,
                  Card::cardValue _changeDirectCard = Card::TEN);
    /**
     * called by a player through the gamecontroller proxy
     * @brief playCard called by a player
     * @param pName name of the player who played a card
     * @param card the played card
     * @param whishedSuit the whised suit if the played card was a wish suit card or Card::NONE
     */
    void playCard(PLAYER::Name pName, const Card& card, Card::cardSuit whishedSuit);
    /**
     *
     * @brief drawCard called by a player if he wants to draw a card
     * @param pName the player who wants to draw
     */
    void drawCard(PLAYER::Name pName);


private:
    void nextTurn();
    void setFlags(const Card& card);
    void setNextPlayer();
    void playerDrawCard(PLAYER::Name pName);
    void handleDraw2x();
    void playerWon(PLAYER::Name playerName);
    std::vector<std::string> getPlayerNames();
};

#endif // GAMECONTROLLER_H
