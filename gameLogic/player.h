#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <string>
#include <vector>
#include "card.h"

//

class Player : public QObject {
    Q_OBJECT
protected:
    std::vector<Card> hand;
    std::string name;
    int playerId;

public
slots:
    virtual void otherPlaysCard(int playerId, const Card& playedCard) = 0;
    virtual void otherDrawsCard(int playerId) = 0;
signals:
    void playCard(int playerId, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(int playerId);
    void doNothing(int playerId);

public:
    //    virtual void addCard(const Card& card) =0;
    virtual void doTurn() = 0;
    virtual void gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int startingPlayer) = 0;
    virtual void reciveCard(const Card& card) = 0;
    //virtualstd::vector<Card> getHand() const = 0;
    virtual int getCardCount() const = 0;
    //virtual void dropCard(const Card& card) = 0;

protected:
   std::vector<Card>& getPlayableCards(const Card& card, Card::cardValue wishSuitCard);
};

#endif // PLAYER_H
