#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <gui/carditem.h>

class Player : public QObject
{
    Q_OBJECT
public:

    enum direction {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3
    };

    explicit Player(direction,short cardCount,QObject *parent = 0);
    QVector<CardItem* > getCards();
private:
    CardItem::specialCards specialCard;
    QVector<CardItem* > cards;

signals:

public slots:

};

#endif // PLAYER_H
