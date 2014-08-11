#include "humanplayer.h"
#include <QDebug>

HumanPlayer::HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController)
    : Player(playerName, _gameController)
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

void HumanPlayer::doTurn(Card::cardSuit wishedSuit)
{
    emit UIdoTurn(this->getPlayableCards(topCard, wishedSuit), wishedSuit);
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

void HumanPlayer::playerWon(PLAYER::Name playerName)
{
    qDebug() << "Player Won, UI doesnt handle it yet";
    emit UIPlayerWon(playerName);
}

void HumanPlayer::UIplaysCard(const Card& card, Card::cardSuit whishedSuit)
{
    dropCard(card);

    gameController.playCard(card, whishedSuit);
    topCard = card;
}

void HumanPlayer::UIdrawsCard()
{
    gameController.drawCard();
}
