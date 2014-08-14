#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "playername.h"
#include <QObject>

/**
 * Each public function has its corresponding function the command is forwarded to.
 * The class uses signals and slots to communicate with the playground.
 * @brief The HumanPlayer class an implementation of the player class to represent a human player
 */
class HumanPlayer : public QObject, public Player {
    Q_OBJECT
public:
    /**
     * @brief HumanPlayer creates an human player
     * @param playerName name or direction of the player
     * @param _gameController the gamecontroller proxy which is used by the player to communicate with the gamecontroller
     * @param title the title or name of the player
     */
    explicit HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);
    /**
     * @brief otherPlaysCard is called when an other player plays a card
     * @param playerName the player who played a card
     * @param playedCard the played card
     */
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    /**
     * @brief otherDrawsCard is called when an other player draws a card
     * @param playerName the player who drew the card
     */
    void otherDrawsCard(PLAYER::Name pName);
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

signals:
    /**
     * @brief UIinitPlayground signal to the ui to init the playground
     * @param humanPlayerCards the starting hand cards
     * @param otherPlayerCardCount the card count of the other players
     * @param topDepotCard the top card on the card depot
     * @param wishSuitCard the card which allowes the players to wish a card suit
     * @param playerNames the names of all players
     */
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards,
                          std::map<PLAYER::Name, int> otherPlayerCardCount,
                          const Card& topDepotCard,
                          Card::cardValue wishSuitCard,
                          std::vector<std::string> playerNames);
    /**
     * @brief UIdoTurn emited to signal the view that the player can play or draw a card
     * @param playableCards the cards the player can play
     * @param wishedSuit the suit which is wished or Card::NONE
     */
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    /**
     * @brief UIplayerPlaysCard emited when an other player  plays a card
     * @param pName the player who played a card
     * @param playedCard the played card
     */
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    /**
     * @brief UIplayerDrawsCard is emited when an other player draws a card
     * @param pName the player who drew a card
     */
    void UIplayerDrawsCard(PLAYER::Name pName);
    /**
     * @brief UIaddPlayerCard is emited when the player adds a card to his hand
     * @param card the added card
     */
    void UIaddPlayerCard(const Card& card);
    /**
     * @brief UIPlayerWon is emited when a palyer won
     * @param _title
     */
    void UIPlayerWon(std::string _title);

public
slots:
    /**
     * @brief UIplaysCard called when the player plays a card
     * @param card the played card
     * @param whishedSuit the wished suit or Card::NONE
     */
    void UIplaysCard(const Card& card, Card::cardSuit whishedSuit);
    /**
     * @brief UIdrawsCard called when the player draws a card
     */
    void UIdrawsCard();
};
#endif // HUMANPLAYER_H
