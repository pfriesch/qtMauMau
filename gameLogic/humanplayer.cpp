#include "humanplayer.h"

HumanPlayer::HumanPlayer(int playerId)

{
    this->playerId = playerId;
}

void HumanPlayer::otherPlaysCard(int playerId, const Card& playedCard)
{
    emit otherPlaysCard(playerId, playedCard);
}

void HumanPlayer::otherDrawsCard(int playerId)
{
    otherDrawsCard(playerId);
}

void HumanPlayer::doTurn()
{
}

void HumanPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int startingPlayer)
{
    this->hand = hand;
    emit initPlayground(hand, otherPlayerCardCount, topCard, startingPlayer);
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
    emit addPlayerCard(card);
}

//vector<Card> HumanPlayer::getHand() const
//{
//  return hand;
//}

int HumanPlayer::getCardCount() const
{
    return hand.size();
}

//void HumanPlayer::dropCard(const Card& card)
//{
//  hand.erase(remove(hand.begin(), hand.end(), card), hand.end());

//}

void HumanPlayer::playCard(const Card& card)
{
    emit playerPlaysCard(playerId, card);
}

void HumanPlayer::drawCard()
{
    emit playerDrawsCard(playerId);
}
