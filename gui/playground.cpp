#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include "gui\playground.h"
#include "cardviewcontroller.h"

Playground::Playground ( QObject * parent ) : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg","jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}


void Playground::init(){
    CardViewController *viewController = new CardViewController;
    viewController->initGame(this);
}
