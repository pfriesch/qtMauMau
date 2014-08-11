#include "player.h"
#include <algorithm>
#include <stdexcept>

PLAYER::Name Player::getPName() const
{
    return playerName;
}

int Player::getCardCount() const
{
    return this->hand.size();
}

Player::Player(PLAYER::Name pName, GameControllerProxy _gameController)
    : playerName(pName)
    , gameController(_gameController)
{
}

std::vector<Card> Player::getPlayableCards(const Card& card, Card::cardSuit wishedSuit)
{
    std::vector<Card> playableCards;
    for (unsigned i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue() || (card.getValue() == wishSuitCard)) {
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
