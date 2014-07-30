//#ifndef REMOTEPLAYER_H
//#define REMOTEPLAYER_H

//#include "player.h"
//#include "network/server.h"

////

//class RemotePlayer : public Player {
//private:
//    Server* server;
//    int playerId;

//public:
//    explicit RemotePlayer(Server* server, int playerId);
//    void otherPlaysCard(int playerId, const Card& playedCard);
//    void otherDrawsCard(int playerId);

//    void doTurn(Card::cardSuit wishSuitCard = Card::NONE);
//    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, int startingPlayer);
//    void reciveCard(const Card& card);
//    int getCardCount() const;
//};

//#endif // REMOTEPLAYER_H
