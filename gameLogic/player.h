#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include "card.h"
#include "gamecontrollerproxy.h"
#include "playername.h"

static const int MAX_PLAYER = 4;
static const int MIN_PLAYER = 2;

/**
 * Each player handled by the gamecontroller needs to be derived from this class.
 * The class provides some common tools needed by all implemented players.
 * @brief The Player class a abstract class to provide a common interface for players
 */
class Player {
public:
    enum Type {
        HUMAN_PLAYER = 0,
        AI_PLAYER = 1,
        REMOTE_PLAYER = 2
    };

protected:
    /**
     * @brief hand the cards the player has in his hand
     */
    std::vector<Card> hand;
    /**
     * @brief playerName the name or direction of the player
     */
    PLAYER::Name playerName;
    /**
     * @brief wishSuitCard the card a player can wish a suit when he plays a card with this vlaue
     */
    Card::cardValue wishSuitCard;
    /**
     * @brief gameController the gamecontroller proxy used to communicate with the gamecontroller
     */
    GameControllerProxy gameController;
    /**
     * @brief title the title or name of the player
     */
    std::string title;

public:
    /**
     * @brief Player creates a player
     * @param playerName name or direction of the player
     * @param _gameController the gamecontroller proxy which is used by the player to communicate with the gamecontroller
     * @param title the title or name of the player
     */
    explicit Player(PLAYER::Name playerName, GameControllerProxy _gameController, std::string title);
    virtual ~Player();
    /**
     * @brief otherPlaysCard is called when an other player plays a card
     * @param playerName the player who played a card
     * @param playedCard the played card
     */
    virtual void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard) = 0;
    /**
     * @brief otherDrawsCard is called when an other player draws a card
     * @param playerName the player who drew the card
     */
    virtual void otherDrawsCard(PLAYER::Name playerName) = 0;
    /**
     * @brief doTurn is called when the player needs to either play or draw a card
     * @param topCard the top card of the card depot which his decision which card he plays is based on
     * @param wishedSuit Card::NONE or the wished suit of the to be played cards
     */
    virtual void doTurn(Card topCard, Card::cardSuit wishedSuit) = 0;
    /**
     * @brief gameInit initializes the player before the game
     * @param hand the starting hand cards
     * @param topCard the top card on the card depot
     * @param otherPlayerCardCount the card count of the other players
     * @param _wishSuitCard the card which allowes the players to wish a card suit
     * @param playerNames the names of all players
     */
    virtual void gameInit(const std::vector<Card> hand,
                          const Card& topCard,
                          std::map<PLAYER::Name, int> otherPlayerCardCount,
                          Card::cardValue _wishSuitCard,
                          std::vector<std::string> playerNames) = 0;
    /**
     * @brief reciveCard is called when the player gets a card
     * @param card the card given to the player
     */
    virtual void reciveCard(const Card& card) = 0;
    /**
     * @brief playerWon is called when a player with the given name won
     * @param _title the name of the winning player
     */
    virtual void playerWon(std::string _title) = 0;
    /**
     * @brief getPName returns the name or direction of the player
     * @return the name or direction of the player
     */
    PLAYER::Name getPName() const;
    /**
     * @brief getCardCount returns the count of the cards in his hand
     * @return the count of the cards in his hand
     */
    int getCardCount() const;
    /**
     * @brief getTitle returns the title or name of the player
     * @return the title or name of the player
     */
    std::string getTitle() const;

protected:
    /**
     * @brief getPlayableCards retruns a vector of cards which can be played, based on the given card and the given wished suit
     * @param card the top depot card
     * @param wishedSuit the wished suit or Card::NONE
     * @return  a vector of cards which can be played, based on the given card and the given wished suit
     */
    std::vector<Card> getPlayableCards(const Card& card, Card::cardSuit wishedSuit);
    /**
     * @brief dropCard the player drops the given card
     * @param card the card to be dropped
     */
    void dropCard(const Card& card);
};

#endif // PLAYER_H
