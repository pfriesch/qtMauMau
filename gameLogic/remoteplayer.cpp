#include "RemotePlayer.h"
#include <QDebug>

RemotePlayer::RemotePlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name)
    : Player(playerName, _gameController, name)
{
    qDebug() << "server: remote Player Name: " << playerName;
}

void RemotePlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    emit RemotePlayerPlaysCard(playerName, pName, playedCard);
}

void RemotePlayer::otherDrawsCard(PLAYER::Name pName)
{
    emit RemotePlayerDrawsCard(playerName, pName);
}

void RemotePlayer::doTurn(Card topCard, Card::cardSuit wishedSuit)
{
    emit RemoteDoTurn(playerName, this->getPlayableCards(topCard, wishedSuit), wishedSuit);
}

void RemotePlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames)
{
    wishSuitCard = _wishSuitCard;
    this->hand = hand;
    emit RemoteInitPlayground(playerName, hand, otherPlayerCardCount, topCard, wishSuitCard, playerNames);
}

void RemotePlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
    emit RemoteAddPlayerCard(playerName, card);
}

void RemotePlayer::playerWon(PLAYER::Name pName)
{
    emit RemotePlayerWon(playerName, pName);
}

void RemotePlayer::RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, Card::cardSuit wishedSuit)
{
    if (playerName == remotePlayerName) {
        dropCard(card);
        gameController.playCard(card, wishedSuit);
    }
}
void RemotePlayer::RemoteDrawsCard(PLAYER::Name remotePlayerName)
{
    if (playerName == remotePlayerName) {
        gameController.drawCard();
    }
}
