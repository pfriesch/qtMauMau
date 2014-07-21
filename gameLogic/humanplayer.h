#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include <QObject>

class HumanPlayer : public QObject, public Player {
    Q_OBJECT
public:
    explicit HumanPlayer(Player::playerName pName);
    void otherPlaysCard(Player::playerName pName, const Card& playedCard);
    void otherDrawsCard(Player::playerName pName);
    void doTurn(Card::cardSuit wishSuitCard, GameControllerProxy gcProxy);
    void doTurn(GameControllerProxy gcProxy);
    void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, Player::playerName startingPlayer);
    void reciveCard(const Card& card);
    int getCardCount() const;

signals:
    void UIinitPlayground(const std::vector<Card>& humanPlayerCards, std::vector<int> otherPlayerCardCount, const Card& topDepotCard, Player::playerName startingPlayer);
    void UIplayerDoTurn(std::vector<Card> playableCards);
    void UIplayerPlaysCard(Player::playerName pName, const Card& playedCard);
    void UIplayerDrawsCard(Player::playerName pName);
    void UIaddPlayerCard(const Card& card);

public
slots:
    void UIplaysCard(const Card& card);
    void UIdrawsCard();
    void UIdoesNothing();
};
#endif // HUMANPLAYER_H
