#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include <QObject>
#include "player.h"

/**
 * Each human player on a remote machine has its own remote player on the server machine.
 * All the public methods are forwarded to thier corresponding signals.
 * These signals are send to the server to be send to the other player on the other machine.
 *
 * @brief The RemotePlayer class represents a remote player on the curren machine
 */
class RemotePlayer : public QObject, public Player {
    Q_OBJECT
public:
    /**
     * @brief RemotePlayer creates an human player
     * @param playerName name or direction of the player
     * @param _gameController the gamecontroller proxy which is used by the player to communicate with the gamecontroller
     * @param name the title or name of the player
     */
    explicit RemotePlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);
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
     * @brief RemoteInitPlayground signal to the server to notify the client to init the playground
     * @param remotePlayerName  the name of the this player
     * @param remotePlayerCards the starting cards of the remote player
     * @param otherPlayerCardCount the card count of all other players
     * @param topDepotCard the top card on the card depot
     * @param wishSuitCard the card which by playing enables  the player to wish a suit
     * @param playerNames names of the other players
     */
    void RemoteInitPlayground(PLAYER::Name remotePlayerName,
                              const std::vector<Card>& remotePlayerCards,
                              std::map<PLAYER::Name, int> otherPlayerCardCount,
                              const Card& topDepotCard,
                              Card::cardValue wishSuitCard,
                              std::vector<std::string> playerNames);
    /**
     * @brief RemoteDoTurn is emited to notify the server to send the remote client a message to do a turn
     * @param remotePlayerName  the name of the this player
     * @param playableCards the cards the client can play
     * @param wishedSuit the suit wich is currently wished or Card::NONE
     */
    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    /**
     * @brief RemotePlayerPlaysCard is emited when a player plays a card and the remote client gets notified about it
     * @param remotePlayerName the name of the this player
     * @param pName the player who played a card
     * @param playedCard the played card
     */
    void RemotePlayerPlaysCard(PLAYER::Name remotePlayerName, PLAYER::Name pName, const Card& playedCard);
    /**
     * @brief RemotePlayerDrawsCard is emited when a player draws a card
     * @param remotePlayerName  the name of the this player
     * @param pName the player who drew a card
     */
    void RemotePlayerDrawsCard(PLAYER::Name remotePlayerName, PLAYER::Name pName);
    /**
     * @brief RemoteAddPlayerCard is emited so the client adds a card to his hand
     * @param remotePlayerName  the name of the this player
     * @param card the card to be added
     */
    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);
    /**
     * @brief RemotePlayerWon is emited to notify the client that a player with the given name won
     * @param remotePlayerName the name of the this player
     * @param _title the name of the player who won
     */
    void RemotePlayerWon(PLAYER::Name remotePlayerName, std::string _title);

public
slots:
    /**
     * @brief RemotePlaysCard communicates the played card with the gamecontroler
     * @param remotePlayerName the name of the this player
     * @param card the played card
     * @param wishedSuit the wished suit or Card::NONE
     */
    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, Card::cardSuit wishedSuit);
    /**
     * @brief RemoteDrawsCard communicates with the gamecontroller that the client drew a card
     * @param remotePlayerName the name of the this player
     */
    void RemoteDrawsCard(PLAYER::Name remotePlayerName);
};

#endif // REMOTEPLAYER_H
