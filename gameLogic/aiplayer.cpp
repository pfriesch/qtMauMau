#include "aiplayer.h"

AIPlayer::AIPlayer(playerName pName, GameControllerProxy _gameController)
    : Player(pName, _gameController)
{
}

void AIPlayer::otherPlaysCard(playerName pName, const Card& playedCard)
{
    topCard = playedCard;
}

void AIPlayer::otherDrawsCard(playerName pName)
{
}

void AIPlayer::doTurn(Card::cardSuit wishSuitCard)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishSuitCard);
    if (playableCards.size() > 0) {
        gameController.playCard(playableCards.at(0));
        dropCard(playableCards[0]);
        drewCard = false;
    } else if (!drewCard) {
        gameController.drawCard();
        drewCard = true;
    } else {
        gameController.doNothing();
        drewCard = false;
    }
}

void AIPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, playerName pName)
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
