#include "humanplayer.h"

HumanPlayer::HumanPlayer(PLAYER::Name pName, GameControllerProxy _gameController)
    : Player(pName, _gameController)
{
}

void HumanPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    topCard = playedCard;
    emit UIplayerPlaysCard(pName, playedCard);
}

void HumanPlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit UIplayerDrawsCard(pName);
}

void HumanPlayer::doTurn(Card::cardSuit wishSuitCard)
{
    if (this->getPlayableCards(topCard, wishSuitCard).size() == 0) {
        gameController.doNothing();
    } else {
        emit UIdoTurn(this->getPlayableCards(topCard, wishSuitCard), wishSuitCard);
    }
}

void HumanPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer)
{
    this->hand = hand;
    this->topCard = topCard;
    emit UIinitPlayground(hand, otherPlayerCardCount, topCard, startingPlayer);
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
    emit UIaddPlayerCard(card);
}

int HumanPlayer::getCardCount() const
{
    return hand.size();
}

void HumanPlayer::UIplaysCard(const Card& card)
{
    gameController.playCard(card);
    dropCard(card);
    drewCard = false;
}

void HumanPlayer::UIdoesNothing()
{
    gameController.doNothing();
    drewCard = false;
}

void HumanPlayer::UIdrawsCard()
{
    if (!drewCard) {
        gameController.drawCard();
        drewCard = true;
    } else {
        //cant draw card
    }
}
