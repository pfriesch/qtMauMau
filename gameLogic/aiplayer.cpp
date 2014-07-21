#include "aiplayer.h"

AIPlayer::AIPlayer(Player::Player::playerName pName)
    : Player(pName)
{
}

void AIPlayer::otherPlaysCard(Player::playerName pName, const Card& playedCard)
{
    topCard = playedCard;
}

void AIPlayer::otherDrawsCard(Player::playerName pName)
{
}

void AIPlayer::doTurn(Card::cardSuit wishSuitCard, GameControllerProxy gcProxy)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishSuitCard);
    if (playableCards.size() > 0) {
        gcProxy.playCard(playableCards.at(0));
        drewCard = false;
    } else if (!drewCard) {
        gcProxy.drawCard();
        drewCard = true;
    } else {
        gcProxy.doNothing();
        drewCard = false;
    }
}

void AIPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, Player::playerName pName)
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
