#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "PlayerName.h"
#include <QObject>

class HumanPlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit HumanPlayer(PLAYER::Name pName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, PLAYER::Name startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, PLAYER::Name startingPlayer);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void UIplayerDrawsCard(PLAYER::Name pName);
    void UIaddPlayerCard(const Card& card);

public
slots:
    void UIplaysCard(const Card& card);
    void UIdrawsCard();

};
#endif // HUMANPLAYER_H
