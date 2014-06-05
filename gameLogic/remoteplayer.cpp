#include "remoteplayer.h"

RemotePlayer::RemotePlayer(Server *server, int playerId)
{
    this->server = server;
    this->playerId = playerId;

}

void RemotePlayer::playerPlaysCard(int playerId, const Card &playedCard)
{
}

void RemotePlayer::playerDrawsCard(int playerId)
{

}

void RemotePlayer::addCard(const Card &card)
{

}

void RemotePlayer::doTurn()
{

}

void RemotePlayer::gameInit(const vector<Card> &hand, const Card &topCard, vector<int> otherPlayerCardCount)
{

}

void RemotePlayer::reciveCard(const Card &card)
{

}

vector<Card> &RemotePlayer::getPlayableCards(const Card &card, Card::cardValue wishSuitCard)
{

}

vector<Card> RemotePlayer::getHand() const
{

}

int RemotePlayer::getCardCount() const
{

}

void RemotePlayer::dropCard(const Card &card)
{

}
