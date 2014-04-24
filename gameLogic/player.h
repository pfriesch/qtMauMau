#ifndef PLAYER_H
#define PLAYER_H


#include <QVector>
#include "card.h"

class Player {
public:
    enum PlayerType {
        human = 0,
        ai = 1,
        remote = 2
    };

private:
    Player::PlayerType playerType;
    QVector<Card> hand;
    QString name;

public:
    explicit Player(Player::PlayerType playerType, QString name);

    void reciveCard(const Card& card);
    void dropCard(const Card& card);
};

#endif // PLAYER_H
