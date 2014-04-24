#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include "gui\playground.h"
#include "cardviewcontroller.h"

Playground::Playground(QObject* parent)
    : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

void Playground::init()
{
    CardViewController* viewController = new CardViewController;
    viewController->initGame(this);
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
