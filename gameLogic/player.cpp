#include "player.h"

int Player::getId() const
{
    return id;
}

vector<Card> Player::getHand() const
{
    return hand;
}

int Player::getCardCount() const
{
    return hand.size();
}

Player::PlayerType Player::getType() const
{
    return playerType;
}

Player::Player(Player::PlayerType playerType, string name)
    : playerType(playerType)
    , name(name)
{
}

void Player::reciveCard(const Card& card)
{
    hand.push_back(card);
}

void Player::dropCard(const Card& card)
{
  hand.erase(remove(hand.begin(), hand.end(),card),hand.end());
}
//TODO specify playable cards
vector<Card>& Player::getPlayableCards(const Card& card)
{
    vector<Card>* playableCards = new vector<Card>;
    for (int i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue()) {
            playableCards->push_back(hand[i]);
        }
    }
    return *playableCards;
}
