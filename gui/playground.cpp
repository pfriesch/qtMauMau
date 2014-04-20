#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include "gui\playground.h"

Playground::Playground ( QObject * parent ) : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg","jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}


void Playground::init(){
    QGraphicsPixmapItem *card = new QGraphicsPixmapItem(QPixmap("img/deck_1/b1fv.png"));
    QPointF centerPoint = this->sceneRect().center();

    centerPoint.setX(centerPoint.x()-card->pixmap().width());
    centerPoint.setY(centerPoint.y()-card->pixmap().height());
    card->setPos(centerPoint);

    QGraphicsPixmapItem *stack = new QGraphicsPixmapItem(QPixmap("img/deck_1/stack.png"));
    centerPoint = this->sceneRect().center();

    centerPoint.setX((centerPoint.x()-stack->pixmap().width())+card->pixmap().width()+10);
    centerPoint.setY(centerPoint.y()-stack->pixmap().height());
    stack->setPos(centerPoint);
    stack->setOpacity(0.6);


    addItem(card);
    addItem(stack);


    //Just testing a player stack

    QGraphicsPixmapItem *card1 = new QGraphicsPixmapItem(QPixmap("img/deck_1/c4.png"));
    card1->setPos(QPointF((this->sceneRect().width()/2)-40,this->sceneRect().width()/2));

    QGraphicsPixmapItem *card2 = new QGraphicsPixmapItem(QPixmap("img/deck_1/hq.png"));
    card2->setPos(QPointF((this->sceneRect().width()/2)-25,this->sceneRect().width()/2));

    addItem(card1);
    addItem(card2);
}
