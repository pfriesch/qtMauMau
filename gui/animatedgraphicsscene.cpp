#include "AnimatedGraphicsScene.h"
#include <QTimeLine>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QDebug>

AnimatedGraphicsScene::AnimatedGraphicsScene ( QObject * parent ) : QGraphicsScene ( parent ), _activeTimeLines (  ), _animationActive ( false )
{
}

/**
 * Prepare the TimeLine with Signal
 * @brief AnimatedGraphicsScene::prepareNewAnimation
 */
void AnimatedGraphicsScene::prepareNewAnimation(QEventLoop &loop)
{
    eventLoop = &loop;
    timeLine = new QTimeLine ( 1500 );
    bool bOk = connect ( timeLine, SIGNAL ( finished() ), this, SLOT ( animationEnded() ) );
    Q_ASSERT ( bOk );
}

void AnimatedGraphicsScene::addPositionAnimation ( QGraphicsPixmapItem * item, QPointF destinationPoint )
{
    item->setZValue(1);
    QPointF srcPos = item->pos();
    if ( srcPos == destinationPoint )
    {
        return ;
    }

    // already animated
    if ( _destinationPositions.contains ( item ) )
    {
        if ( destinationPoint == _destinationPositions[item] )
        {
            return;
        }
        // as long as this item is already being animated
        // the src pos will be this
        srcPos = _destinationPositions[item];
    }

    _destinationPositions[item] = destinationPoint;

    newAnimation = new QGraphicsItemAnimation ( timeLine );
    newAnimation->setTimeLine ( timeLine );
    newAnimation->setItem ( item );
    newAnimation->setPosAt ( 0, srcPos );
    newAnimation->setPosAt ( 1, destinationPoint );
}



void AnimatedGraphicsScene::startAnimation()
{
    //_activeTimeLine->start();

    if ( _animationActive == false )
    {
        _animationActive = true;
        timeLine->start();
    }
    else
    {
        _activeTimeLines.enqueue ( timeLine );
    }
}

void AnimatedGraphicsScene::animationEnded()
{
    // restart
    if ( _activeTimeLines.size() == 0)
    {
        _animationActive = false;
        _destinationPositions.clear();
        delete timeLine;
<<<<<<< HEAD
      //  newAnimation->item()->setZValue(0);
        eventLoop->exit();
=======
/*
        if(newAnimation != NULL && newAnimation->item() != NULL){
            newAnimation->item()->setZValue(0);
        }
  */
      eventLoop->exit();
>>>>>>> master
        return;
    }
    QTimeLine * x = _activeTimeLines.dequeue();
    qDebug() << "Starting time line: " << x;
    x->start();
}
