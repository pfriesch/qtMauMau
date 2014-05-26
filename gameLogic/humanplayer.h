#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <algorithm>
#include "player.h"




class HumanPlayer : public Player {
public:
    enum PlayerType {
        human = 0,
        ai = 1,
        remote = 2
    };

private:
    HumanPlayer::PlayerType playerType;
    vector<Card> hand;
    string name;

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
