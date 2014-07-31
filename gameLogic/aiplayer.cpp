#include "aiplayer.h"

AIPlayer::AIPlayer(PLAYER::Name pName, GameControllerProxy _gameController)
    : Player(pName, _gameController)
{
}

void AIPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    topCard = playedCard;
}

void AIPlayer::otherDrawsCard(PLAYER::Name pName)
{
}

void AIPlayer::doTurn(Card::cardSuit wishSuitCard)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishSuitCard);
    if (playableCards.size() > 0) {
        //TODO ai choose better card
        Card playCard = playableCards.at(0);
        dropCard(playableCards.at(0));
        gameController.playCard(playCard);
    } else {

        gameController.drawCard();
    }
}

void AIPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name pName)
{
    this->hand = hand;
    this->topCard = topCard;
    this->pName = pName;
}

void AIPlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
}

int AIPlayer::getCardCount() const
{
    return this->hand.size();
}
