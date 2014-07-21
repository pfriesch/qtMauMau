#include "humanplayer.h"

HumanPlayer::HumanPlayer(Player::playerName pName)
    : Player(pName)
{
}

void HumanPlayer::otherPlaysCard(Player::playerName pName, const Card& playedCard)
{
    topCard = playedCard;
    emit UIplayerPlaysCard(pName, playedCard);
}

void HumanPlayer::otherDrawsCard(Player::playerName pName)
{
    emit UIplayerDrawsCard(pName);
}

void HumanPlayer::doTurn(Card::cardSuit wishSuitCard, GameControllerProxy gcProxy)
{
}

void HumanPlayer::doTurn(GameControllerProxy gcProxy)
{
}

void HumanPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, Player::playerName startingPlayer)
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

void HumanPlayer::UIplaysCard(const Card& card)
{
    gameController->playCard(card);
    drewCard = false;
}

void HumanPlayer::UIdoesNothing()
{
    gameController->doNothing();
    drewCard = false;
}

void HumanPlayer::UIdrawsCard()
{
    if (!drewCard) {
        gameController->drawCard();
        drewCard = true;
    } else {
        //cant draw card
    }
}
