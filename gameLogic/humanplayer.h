#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"

class HumanPlayer : public Player {
  Q_OBJECT
public:
    explicit HumanPlayer(int playerId);
    void otherPlaysCard(int playerId, const Card& playedCard);
    void otherDrawsCard(int playerId);
    void doTurn();
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;
    //void dropCard(const Card& card);

signals:
    void initPlayground(const std::vector<Card>& humanPlayerCards, std::vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer);
    void playerDoTurn(std::vector<Card> playableCards);
    void playerPlaysCard(int player, const Card& playedCard);
    void playerDrawsCard(int player);
    void addPlayerCard(const Card& card);

public
slots:
    void playCard(const Card& card);
    void drawCard();
};
#endif // HUMANPLAYER_H
