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
#include <QEventLoop>
#include <QDialog>
#include <gameLogic/gamecontroller.h>
#include <gameLogic/Card.h>
#include <gui/carditem.h>
#include <gui/playeritem.h>
#include <gui/animatedgraphicsscene.h>

class Playground : public AnimatedGraphicsScene {
    Q_OBJECT
public:
    explicit Playground(QObject* parent = 0);
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:

    QVector<CardItem*> graphicalItems;
    QHash<PlayerItem::direction,PlayerItem*> players;

    CardItem depot;
    CardItem stack;

    void updateDepotCard(CardItem &fromCard, CardItem &toCard, bool withAnimation = true);
    void updatePlayerCard(CardItem &fromCard, CardItem &toCard, bool withAnimation = true);
    void createPlayer(const std::vector<Card>& humanPlayerCards, std::vector<int> otherPlayerCardCount);
    void chooseColor();

    //Layout entities
    int cardWidth = 71;
    int cardHeight = 96;
    int horizontalCardGap = 15;
    int verticalCardGap = 20;

public
slots:

    void initPlayground(const std::vector<Card>& humanPlayerCards, std::vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer);
    //bekomme alle Karten und anzahl karten der anderen Mitspieler

    void playerDoTurn(std::vector<Card> playableCards);
    // bekomme alle Spielbaren Karten von Human player

    void playerPlaysCard(int player, const Card& playedCard);
    // Spieler spielt eine Karte und welche

    void playerDrawsCard(short player);
    // Spieler zieht eine Karte

    void addPlayerCard(const Card& card);
// Human Spieler hat eine Karte gezogen

signals:
    void playCard(const Card& card);
    void drawCard();
};

#endif // PLAYGROUND_H
