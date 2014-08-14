#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

/**
 * @brief The AIPlayer class is an implementation of the player class as computer controlled player
 */
class AIPlayer : public Player {
#ifdef TEST
    friend class AIPlayer_test;
#endif
public:
    /**
     * @brief Player creates an ai player
     * @param playerName name or direction of the player
     * @param _gameController the gamecontroller proxy which is used by the player to communicate with the gamecontroller
     * @param title the title or name of the player
     */
    explicit AIPlayer(PLAYER::Name playerName,
                      GameControllerProxy _gameController,
                      std::string name);
    /**
     * @brief otherPlaysCard is called when an other player plays a card
     * @param playerName the player who played a card
     * @param playedCard the played card
     */
    void otherPlaysCard(PLAYER::Name playerName, const Card& playedCard);
    /**
     * @brief otherDrawsCard is called when an other player draws a card
     * @param playerName the player who drew the card
     */
    void otherDrawsCard(PLAYER::Name playerName);
    /**
     * @brief doTurn is called when the player needs to either play or draw a card
     * @param topCard the top card of the card depot which his decision which card he plays is based on
     * @param wishedSuit Card::NONE or the wished suit of the to be played cards
     */
    void doTurn(Card topCard, Card::cardSuit wishedSuit);
    /**
     * @brief gameInit initializes the player before the game
     * @param hand the starting hand cards
     * @param topCard the top card on the card depot
     * @param otherPlayerCardCount the card count of the other players
     * @param _wishSuitCard the card which allowes the players to wish a card suit
     * @param playerNames the names of all players
     */
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  Card::cardValue _wishSuitCard,
                  std::vector<std::string> playerNames);
    /**
     * @brief reciveCard is called when the player gets a card
     * @param card the card given to the player
     */
    void reciveCard(const Card& card);
    /**
     * @brief playerWon is called when a player with the given name won
     * @param _title the name of the winning player
     */
    void playerWon(std::string _title);

private:
    Card getPlayCard(std::vector<Card> playableCards);
    Card::cardSuit getWhishedCardSuit();
};

#endif // AIPLAYER_H
