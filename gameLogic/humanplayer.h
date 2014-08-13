#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "PlayerName.h"
#include <QObject>

class HumanPlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit HumanPlayer(PLAYER::Name playerName, GameControllerProxy _gameController);
    void otherPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void otherDrawsCard(PLAYER::Name pName);
    void doTurn(Card topCard, Card::cardSuit wishedSuit);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, Card::cardValue _wishSuitCard);
    void reciveCard(const Card& card);
    void playerWon(PLAYER::Name pName);

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards,
                          std::map<PLAYER::Name, int> otherPlayerCardCount,
                          const Card& topDepotCard,
                          Card::cardValue wishSuitCard);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void UIplayerDrawsCard(PLAYER::Name pName);
    void UIaddPlayerCard(const Card& card);
    void UIPlayerWon(PLAYER::Name pName);

public
slots:
    void UIplaysCard(const Card& card, Card::cardSuit whishedSuit);
    void UIdrawsCard();
};
#endif // HUMANPLAYER_H
