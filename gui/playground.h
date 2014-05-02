#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <gameLogic/gamecontroller.h>
#include <gameLogic/Card.h>
#include <QVector>
#include <QPointF>

class Playground : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Playground( QObject * parent = 0 );
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void fakeInit();
    void fakeDoTurn();
    int width;
    int height;
    QPointF centerPoint;

public slots:

void initPlayground(QVector<Card> *humanPlayerCards, QVector<short> otherPlayerCardCount, Card& topDepotCard, short startingPlayer);
//bekomme alle Karten und anzahl karten der anderen Mitspieler

void playerDoTurn(QVector<Card> *playableCards);
// bekomme alle Spielbaren Karten von Human player

void playerPlaysCard(short player, Card& playedCard);
// Spieler spielt eine Karte und welche

void playerDrawsCard(short player, Card& card);
// Spieler zieht eine Karte

void addPlayerCard(const Card& card);
// Human Spieler hat eine Karte gezogen

signals:
    void playCard(const Card& card);
    void drawCard();
};

#endif // PLAYGROUND_H
