#include "player.h"
#include <algorithm>
#include <stdexcept>

PLAYER::Name Player::getPName() const
{
    return pName;
}

Player::Player(PLAYER::Name pName, GameControllerProxy _gameController)
    : pName(pName)
    , gameController(_gameController)
{
}

std::vector<Card> Player::getPlayableCards(const Card& card, Card::cardSuit wishSuitCard)
{
    std::vector<Card> playableCards;
    for (unsigned int i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue() || card.getSuit() == wishSuitCard) {
            playableCards.push_back(hand[i]);
        }
    }
    return playableCards;
}

void Player::dropCard(const Card& card)
{
    std::vector<Card>::iterator pos = std::find(hand.begin(), hand.end(), card);

    if (pos != hand.end()) {
        hand.erase(pos);
    } else {
        throw std::range_error("Card not found in hand.");
    }
}
