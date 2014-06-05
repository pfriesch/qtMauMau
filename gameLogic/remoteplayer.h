#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "player.h"
#include "network/server.h"

using namespace std;

class RemotePlayer : public Player
{
public:
    explicit RemotePlayer(Server *server, int playerId);
    void playerPlaysCard(int playerId, const Card& playedCard);
    void playerDrawsCard(int playerId);

    void addCard(const Card& card);
    void doTurn();
    void gameInit(const vector<Card>& hand, const Card& topCard, vector<int> otherPlayerCardCount);
    void reciveCard(const Card& card);
    vector<Card> &getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
    vector<Card> getHand() const;
    int getCardCount() const;
    void dropCard(const Card& card);

private:
    Server *server;
    int playerId;
};

#endif // REMOTEPLAYER_H
