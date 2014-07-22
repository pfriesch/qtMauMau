#include "player.h"


playerName Player::getPName() const
{
    return pName;
}

Player::Player(playerName pName, GameControllerProxy _gameController)
    : pName(pName)
    , gameController(_gameController)
{
}

std::vector<Card>& Player::getPlayableCards(const Card& card, Card::cardSuit wishSuitCard)
{
    std::vector<Card>* playableCards = new std::vector<Card>;
    for (unsigned int i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue() || card.getSuit() == wishSuitCard) {
            playableCards->push_back(hand[i]);
        }
    }
    return *playableCards;
}
