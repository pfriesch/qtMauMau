#include "player.h"

int Player::getId() const
{
    return id;
}

QVector<Card> Player::getHand() const
{
  return hand;
}

int Player::getCardCount() const
{
  return hand.length();
}

Player::Player(Player::PlayerType playerType, QString name)
    : playerType(playerType)
    , name(name)
{
}

void Player::reciveCard(const Card& card)
{
    hand.append(card);
}

void Player::dropCard(const Card& card)
{
  hand.remove(hand.indexOf(card));
}

QVector<Card> &Player::getPlayableCards(const Card &card)
{

}
