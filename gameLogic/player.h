#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <algorithm>
#include "card.h"

using namespace std;

class Player {
public:
    enum PlayerType {
        human = 0,
        ai = 1,
        remote = 2
    };

private:
    Player::PlayerType playerType;
    vector<Card> hand;
    string name;
    int id;

public:
    explicit Player(Player::PlayerType playerType = Player::PlayerType(1), string name = "");
    void reciveCard(const Card& card);
    void dropCard(const Card& card);
    vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    int getId() const;
    vector<Card> getHand() const;
    int getCardCount() const;
    Player::PlayerType getType() const;
};

#endif // PLAYER_H
