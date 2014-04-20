#include "cardviewcontroller.h"
#include <QGraphicsPixmapItem>
#include <QPointer>

CardViewController::CardViewController(QObject *parent) : QObject(parent) {
}


void CardViewController::initGame(QGraphicsScene *scene) {

    // Setup Stack
    QGraphicsPixmapItem *stack = new QGraphicsPixmapItem(QPixmap("img/deck_1/b1fv.png"));
    QPointF centerPoint = scene->sceneRect().center();

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


    //Just testing a player stack
    QGraphicsPixmapItem *card1 = new QGraphicsPixmapItem(QPixmap("img/deck_1/c4.png"));
    card1->setPos(QPointF((scene->sceneRect().width()/2)-40,scene->sceneRect().width()/2));

    QGraphicsPixmapItem *card2 = new QGraphicsPixmapItem(QPixmap("img/deck_1/hq.png"));
    card2->setPos(QPointF((scene->sceneRect().width()/2)-25,scene->sceneRect().width()/2));


    scene->addItem(card1);
    scene->addItem(card2);
}
