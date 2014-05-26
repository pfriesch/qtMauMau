#include "humanplayer.h"

vector<Card> HumanHumanPlayer::getHand() const
{
    return hand;
}

int HumanHumanPlayer::getCardCount() const
{
    return hand.size();
}

HumanHumanPlayer::PlayerType HumanPlayer::getType() const
{
    return playerType;
}

HumanPlayer::Player(HumanPlayer::PlayerType playerType, string name)
    : playerType(playerType)
    , name(name)
{
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
}

void HumanPlayer::dropCard(const Card& card)
{
    hand.erase(remove(hand.begin(), hand.end(), card), hand.end());
}
//TODO specify playable cards
vector<Card>& HumanPlayer::getPlayableCards(const Card& card, Card::cardValue wishSuitCard)
{
    vector<Card>* playableCards = new vector<Card>;
    for (unsigned int i = 0; i < hand.size(); ++i) {
        if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue() || card.getValue() == wishSuitCard) {
            playableCards->push_back(hand[i]);
        }
    }
    return *playableCards;
}
