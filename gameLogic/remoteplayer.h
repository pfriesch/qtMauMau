#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include <QObject>
#include "player.h"

class RemotePlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit RemotePlayer(PLAYER::Name playerName, GameControllerProxy _gameController, std::string name);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card topCard, Card::cardSuit wishedSuit);
    void gameInit(const std::vector<Card> hand,
                  const Card& topCard,
                  std::map<PLAYER::Name, int> otherPlayerCardCount,
                  Card::cardValue _wishSuitCard,
                  std::vector<std::string> playerNames);
    void reciveCard(const Card& card);
    void playerWon(PLAYER::Name pName);

signals:
    void RemoteInitPlayground(PLAYER::Name remotePlayerName,
                              const std::vector<Card>& remotePlayerCards,
                              std::map<PLAYER::Name, int> otherPlayerCardCount,
                              const Card& topDepotCard,
                              Card::cardValue wishSuitCard,
                              std::vector<std::string> playerNames);
    void RemoteDoTurn(PLAYER::Name remotePlayerName, std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    void RemotePlayerPlaysCard(PLAYER::Name remotePlayerName, PLAYER::Name pName, const Card& playedCard);
    void RemotePlayerDrawsCard(PLAYER::Name remotePlayerName, PLAYER::Name pName);
    void RemoteAddPlayerCard(PLAYER::Name remotePlayerName, const Card& card);
    void RemotePlayerWon(PLAYER::Name remotePlayerName, PLAYER::Name pName);

public
slots:
    void RemotePlaysCard(PLAYER::Name remotePlayerName, const Card& card, Card::cardSuit wishedSuit);
    void RemoteDrawsCard(PLAYER::Name remotePlayerName);
};

#endif // REMOTEPLAYER_H
