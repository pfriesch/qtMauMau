#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include <QObject>
#include "player.h"

class RemotePlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit RemotePlayer(PLAYER::Name pName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

signals:
    void RemoteInitPlayground(PLAYER::Name remotePlayerName, const std::vector<Card>& remotePlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer);
    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void RemotePlayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void RemotePlayerDrawsCard(PLAYER::Name pName);
    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);

public
slots:
    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card);
    void RemoteDrawsCard(PLAYER::Name remotePlayerName);
};

#endif // REMOTEPLAYER_H