#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include "gui\playground.h"

Playground::Playground ( QObject * parent ) : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg","jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}


void Playground::startGame(){

    gameController.startGame();
    /*
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
    */
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsItem *item = itemAt(event->buttonDownScenePos(event->button()),QTransform());
  if (item == NULL)
  {
    // do stuff if not clicked on an item
  }
  else
  {

    //signal to GameController
   // QGraphicsScene::mousePressEvent(event); // this forwards the event to the item
  }
}
