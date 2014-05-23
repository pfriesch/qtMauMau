#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <gui/carditem.h>
#include <vector>
#include <QDebug>
#include <QString>
#include <QGraphicsColorizeEffect>
#include <QGraphicsTextItem>
#include <QColor>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <QString>
#include <QPainter>
#include <QTextCursor>

class PlayerItem : public QObject {
    Q_OBJECT
public:
    enum direction {
        LEFT = 1,
        TOP = 2,
        RIGHT = 3,
        HUMAN = 4
    };

    PlayerItem(direction dir, int cardCount, QPointF centerPoint, QString _playername, QObject* parent = 0);
    PlayerItem(direction dir, std::vector<Card> humanCards, QPointF centerPoint, QString _playername);
    void createCards(int cardCount);
    void setPlayableCards(std::vector<Card> playableCards);
    void unsetPlayableCards();
    direction getDirection();
    QVector<CardItem*>* getCards();
    void removeCard(const Card& card);
    CardItem* addCard(const Card& card);
    CardItem* findCard(const Card& card);
    CardItem::specialCards getSpecialCard();
    QGraphicsTextItem* getPlayername();
    void setActive();
    void setUnactive();
    ~PlayerItem();

private:
    void measureLayout(int cardCount);
    void createHumanCards(std::vector<Card> humanCards);
    QVector<CardItem*>* cards = new QVector<CardItem*>();
    CardItem::specialCards specialCard;
    PlayerItem::direction playerDirection;
    QPointF centerPoint;

    QGraphicsTextItem *playername;

    int nameX;
    int nameY;
    int x;
    int y;

    //TODO: set in config.ini not in the code
    int cardWidth = 71;
    int cardHeight = 96;
    int cardGap = 20;
    int borderMargin = 30;
    int offsetPlayableCard = 20;

signals:

public
slots:
};

#endif // PLAYERITEM_H
