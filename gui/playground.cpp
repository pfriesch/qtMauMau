#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include "gui\playground.h"
#include "gui/carditem.h"

Playground::Playground(QObject* parent): QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    this->width = 71;
    height = 96;
    centerPoint = QPointF(&sceneRect().center().QPointF);
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

void Playground::startGame(){
    qDebug() << centerPoint->x();
    CardItem stack(CardItem::specialCards::RED_VERTICAL);
    QGraphicsPixmapItem *stackItem = stack.getGraphicsItem();
    stackItem->setPos(centerPoint->x()-stackItem->pixmap().width(),centerPoint->y()-stackItem->pixmap().height());
    this->addItem(stackItem);

    CardItem talon(CardItem::specialCards::TALON);
    QGraphicsPixmapItem *talonItem = talon.getGraphicsItem();
    talonItem->setPos((centerPoint->x()-talonItem->pixmap().width())+width+20,centerPoint->y()-talonItem->pixmap().height());
    this->addItem(talonItem);




    fakeInit();

    /*
    QGraphicsPixmapItem *stack = new QGraphicsPixmapItem(QPixmap("img/deck_1/b1fv.png"));


    centerPoint.setX(centerPoint.x()-stack->pixmap().width());
    centerPoint.setY(centerPoint.y()-stack->pixmap().height());
    stack->setPos(centerPoint);

    // Setup Depot
    QGraphicsPixmapItem *depot = new QGraphicsPixmapItem(QPixmap("img/deck_1/depot.png"));
    centerPoint = scene->sceneRect().center();

    centerPoint.setX((centerPoint.x()-stack->pixmap().width())+depot->pixmap().width()+10);
    centerPoint.setY(centerPoint.y()-stack->pixmap().height());
    depot->setPos(centerPoint);
    depot->setOpacity(0.6);


    scene->addItem(stack);
    scene->addItem(depot);
    */
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item == NULL) {
        // do stuff if not clicked on an item
    } else {

        //signal to GameController
        // QGraphicsScene::mousePressEvent(event); // this forwards the event to the item
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
void Playground::initPlayground(QVector<Card> *humanPlayerCards, QVector<short> otherPlayerCardCount, Card& topDepotCard, short startingPlayer){
}


// bekomme alle Spielbaren Karten von Human player
void Playground::playerDoTurn(QVector<Card> *playableCards){

}

// Spieler spielt eine Karte und welche
void Playground::playerPlaysCard(short player, Card& playedCard){

}

// Spieler zieht eine Karte
void Playground::playerDrawsCard(short player, Card& card){

}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card){

}

void Playground::fakeInit(){


}
