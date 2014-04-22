#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector>
#include "card.h"

namespace Player {
  enum PlayerType{
    human = 0,
    ai = 1,
    remote = 2
  };
}

class Player : public QObject
{

  Q_OBJECT

private:
  Player::PlayerType playerType;
  QVector<Card> *hand;
  QString name;
  Player& operator = (const Player &Player);
  void Player(const Player &Player);

public:
  explicit Player(Player::PlayerType playerType, QString name);
  virtual ~Player();
  void reciveCard(const Card &card);
  void dropCard(const Card &card);

signals:

public slots:


};

#endif // PLAYER_H
