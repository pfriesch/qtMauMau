#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <gui/carditem.h>
#include <QDebug>

class PlayerItem : public QObject {
    Q_OBJECT
public:
    enum direction {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3,
    };

    PlayerItem(direction dir, short cardCount, QPointF centerPoint, QObject* parent = 0);
    QVector<CardItem*> getCards();

private:
    void measureLayout(short cardCount);
    QVector<CardItem*> cards;
    CardItem::specialCards specialCard;
    int cardWidth;
    int cardHeight;
    int horizontalCardGap = 15;
    int verticalCardGap = 20;
    QHash<QString, int> layout;
    QPointF centerPoint;

signals:

public
slots:
};

#endif // PLAYERITEM_H
