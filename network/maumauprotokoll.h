#ifndef MAUMAUPROTOKOLL_H
#define MAUMAUPROTOKOLL_H

#include <QString>
#include <vector>
#include "gameLogic/Card.h"
#include <map>
#include "gameLogic/PlayerName.h"

//MauMauProtokoll
class MProtocol {
public:
    enum toClient {
        INIT_PLAYGROUND = 0,
        DO_TURN = 1,
        OTHER_PLAYS_CARD = 2,
        OTHER_DRAWS_CARD = 3,
        ADD_CARD = 4,
    };
    enum toServer {
        PLAY_CARD = 0,
        DRAW_CARD = 1
    };

public:
    MProtocol();
    static QString cardVectorToSting(std::vector<Card> cards);
    static QString playerCardCountToSting(std::map<PLAYER::Name, int> otherPlayerCardCount);
    static QString cardToSting(Card card);

    static std::vector<Card> stringToCardVec(QString vecAsSting);
    static std::map<PLAYER::Name, int> stingToCardCountMap(QString mapAsSting);
    static Card stingToCard(QString cardAsSting);
};

#endif // MAUMAUPROTOKOLL_H
