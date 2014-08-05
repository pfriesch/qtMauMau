#include "RemotePlayer.h"
#include <QDebug>

RemotePlayer::RemotePlayer(PLAYER::Name pName, GameControllerProxy _gameController)
    : Player(pName, _gameController)
{
    qDebug() << "server: remote Player Name: " << pName;
}

void RemotePlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    topCard = playedCard;
    emit RemotePlayerPlaysCard(pName, playedCard);
}

void RemotePlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit RemotePlayerDrawsCard(pName);
}

void RemotePlayer::doTurn(Card::cardSuit wishSuitCard)
{
    emit RemoteDoTurn(pName, this->getPlayableCards(topCard, wishSuitCard), wishSuitCard);
}

void RemotePlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer)
{
    this->hand = hand;
    this->topCard = topCard;
    emit RemoteInitPlayground(pName, hand, otherPlayerCardCount, topCard, startingPlayer);
}

void RemotePlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
    emit RemoteAddPlayerCard(pName, card);
}

int RemotePlayer::getCardCount() const
{
    return this->hand.size();
}
void RemotePlayer::RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card)
{
    if (pName == remotePlayerName) {
        dropCard(card);
        gameController.playCard(card);
    }
}
void RemotePlayer::RemoteDrawsCard(PLAYER::Name remotePlayerName)
{
    if (pName == remotePlayerName) {
        gameController.drawCard();
    }
}
