#ifndef MAUMAUPROTOKOLL_H
#define MAUMAUPROTOKOLL_H

#include <QString>
#include <vector>
#include <string>
#include "gameLogic/card.h"
#include <map>
#include "gameLogic/playername.h"

/**
 *
 * @brief The MProtocol class holds static methods to encode and decode network communication done by a mau mau game.
 */
class MProtocol {
public:
    enum toClient {
        INIT_PLAYGROUND = 0,
        DO_TURN = 1,
        OTHER_PLAYS_CARD = 2,
        OTHER_DRAWS_CARD = 3,
        ADD_CARD = 4,
        PLAYER_WON = 5,
        REQUEST_NAME = 10,
        CONNECTION_REJECTED = 11,
        CONNECTION_ACCEPTED = 12
    };
    enum toServer {
        PLAY_CARD = 0,
        DRAW_CARD = 1,
        SEND_NAME = 10
    };

public:
    MProtocol();
    static QString cardVectorToSting(std::vector<Card> cards);
    static QString playerCardCountToSting(std::map<PLAYER::Name, int> otherPlayerCardCount);
    static QString cardToSting(Card card);
    static QString stringVecToSingle(std::vector<std::string> playerNames);

    static std::vector<std::string> stringToStringVec(QString stringVec);
    static std::vector<Card> stringToCardVec(QString vecAsSting);
    static std::map<PLAYER::Name, int> stingToCardCountMap(QString mapAsSting);
    static Card stingToCard(QString cardAsSting);
};

#endif // MAUMAUPROTOKOLL_H
