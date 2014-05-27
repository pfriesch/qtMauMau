#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <QObject>
#include <algorithm>
#include "player.h"

class HumanPlayer : public Player, public QObject {
    Q_OBJECT
public:

private:
    HumanPlayer::PlayerType playerType;
    vector<Card> hand;
    string name;

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

public:
    explicit HumanPlayer(Player::PlayerType playerType = Player::PlayerType(1), string name = "");
    void reciveCard(const Card& card);
    void dropCard(const Card& card);
    vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    vector<Card> getHand() const;
    int getCardCount() const;
    Player::PlayerType getType() const;
};

#endif // HUMANPLAYER_H
