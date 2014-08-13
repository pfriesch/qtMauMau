#include "humanplayer.h"
#include <QDebug>

HumanPlayer::HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController)
    : Player(playerName, _gameController)
{
}

void HumanPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    emit UIplayerPlaysCard(pName, playedCard);
}

void HumanPlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit UIplayerDrawsCard(pName);
}

void HumanPlayer::doTurn(Card topCard, Card::cardSuit wishedSuit)
{
    emit UIdoTurn(this->getPlayableCards(topCard, wishedSuit), wishedSuit);
}

void HumanPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, Card::cardValue _wishSuitCard)
{
    wishSuitCard = _wishSuitCard;
    this->hand = hand;
    emit UIinitPlayground(hand, otherPlayerCardCount, topCard, wishSuitCard);
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
    emit UIaddPlayerCard(card);
}

void HumanPlayer::playerWon(PLAYER::Name playerName)
{
    qDebug() << "Player Won, UI doesnt handle it yet";
    emit UIPlayerWon(playerName);
}

void HumanPlayer::UIplaysCard(const Card& card, Card::cardSuit whishedSuit)
{
    dropCard(card);
    gameController.playCard(card, whishedSuit);
}

void HumanPlayer::UIdrawsCard()
{
    gameController.drawCard();
}
