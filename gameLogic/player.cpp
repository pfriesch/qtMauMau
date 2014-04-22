#include "player.h"

Player::Player(Player::PlayerType playerType, QString name) :
  playerType(playerType), name(name)
{
  hand = new QVector<Card>;
}

Player::~Player()
{
  delete hand;
}

void Player::reciveCard(const Card &card)
{
  hand->append(card);
}

void Player::dropCard(const Card &card)
{
  hand->remove(hand->indexOf(card));
}
