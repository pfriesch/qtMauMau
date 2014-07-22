#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include "PlayerNames.h"
#include <QObject>

class HumanPlayer : public QObject, public Player {
    Q_OBJECT

//    std::vector<Card> hand;
//    std::string name;
//    playerName pName;
//    Card topCard;
//    bool drewCard = false;
//    GameControllerProxy gameController;

public:
    explicit HumanPlayer(playerName pName, GameControllerProxy _gameController);
    void otherPlaysCard(playerName pName, const Card& playedCard);
    void otherDrawsCard(playerName pName);
    void doTurn(Card::cardSuit wishSuitCard);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, playerName startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards, std::map<playerName, int> otherPlayerCardCount, const Card& topDepotCard, playerName startingPlayer);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishSuitCard);
    void UIplayerPlaysCard(playerName pName, const Card& playedCard);
    void UIplayerDrawsCard(playerName pName);
    void UIaddPlayerCard(const Card& card);

public
slots:
    void UIplaysCard(const Card& card);
    void UIdrawsCard();
    void UIdoesNothing();
};
#endif // HUMANPLAYER_H
