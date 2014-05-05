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

Player::PlayerType Player::getType() const
{
    return playerType;
}

Player::Player(Player::PlayerType playerType, QString name)
    : playerType(playerType), name(name)
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
//TODO
QVector<Card>& Player::getPlayableCards(const Card& card)
{
    QVector<Card>* playableCards = new QVector<Card>;
    for (int i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue()) {
            playableCards->append(hand[i]);
        }
    }
    return *playableCards;
}
