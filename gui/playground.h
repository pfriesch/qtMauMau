#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>
#include <QHash>
#include <QString>
#include <vector>
#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include <gameLogic/gamecontroller.h>
#include <gameLogic/Card.h>
#include <gui/carditem.h>
#include <gui/playeritem.h>

class Playground : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Playground(QObject* parent = 0);
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
   // void fakeInit();


    QVector<CardItem*> graphicalItems;
    QHash<PlayerItem::direction,PlayerItem*> players;

    CardItem depot;
    CardItem stack;

    void updateCard(CardItem& card, const Card newCard);
    void createPlayer(const vector<Card>& humanPlayerCards,vector<int> otherPlayerCardCount);

    //Layout entities
    void measureLayout();
    int cardWidth = 71;
    int cardHeight = 96;
    int horizontalCardGap = 15;
    int verticalCardGap = 20;
    QHash<QString, int> layout;

public
slots:

    void initPlayground(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer);
    //bekomme alle Karten und anzahl karten der anderen Mitspieler

    void playerDoTurn(vector<Card> playableCards);
    // bekomme alle Spielbaren Karten von Human player

    void playerPlaysCard(int player, const Card& playedCard);
    // Spieler spielt eine Karte und welche
/*
    void playerDrawsCard(short player, Card& card);
    // Spieler zieht eine Karte

    void addPlayerCard(const Card& card);*/
// Human Spieler hat eine Karte gezogen

signals:
    void playCard(const Card& card);
    void drawCard();
};

#endif // PLAYGROUND_H
