#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <gui/carditem.h>
#include <QDebug>
#include <QString>

class PlayerItem : public QObject {
    Q_OBJECT
public:
    enum direction {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3,
        BOTTOM = 4
    };

    PlayerItem(direction dir, short cardCount, QPointF centerPoint, QObject* parent = 0);
    PlayerItem(direction dir, QVector<Card> *humanCards, QPointF centerPoint);
    QVector<CardItem*>* getCards();
    void createCards(short cardCount);
private:
    void measureLayout(short cardCount);
    void createHumanCards(QVector<Card> *humanCards);
    QVector<CardItem*> *cards = new QVector<CardItem*>();
    CardItem::specialCards specialCard;
    PlayerItem::direction playerDirection;
    QString layoutKey;
    QHash<QString, int> layout;
    QPointF centerPoint;

    //TODO: set in config.ini not in the code
    int cardWidth = 71;
    int cardHeight = 96;
    int cardGap = 20;

signals:

public
slots:
};

#endif // PLAYERITEM_H
