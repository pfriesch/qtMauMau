#include "animatedgraphicsscene.h"
#include <QTimeLine>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <settings.h>

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
    timeLine = new QTimeLine ( Settings::getInstance()->getProperty("common/animation_velocity").toInt() );
    bool bOk = connect ( timeLine, SIGNAL ( finished() ), this, SLOT ( animationEnded() ) );
    Q_ASSERT ( bOk );
}
/**
    * Add Position from one point to an other point
    * @brief AnimatedGraphicsScene::addPositionAnimation
    * @param item
    * @param destinationItem
    */
void AnimatedGraphicsScene::addPositionAnimation ( QGraphicsPixmapItem &item, QGraphicsPixmapItem &destinationItem )
{
    //item->setZValue(1);
    QPointF srcPos = item.pos();
    /*if ( srcPos == destinationPoint )
    {
        return;
    }*/

    // already animated
    if ( _destinationPositions.contains ( &item ) )
    {
        if ( destinationItem.pos() == _destinationPositions[&item] )
        {
            return;
        }
        // as long as this item is already being animated
        // the src pos will be this
        srcPos = _destinationPositions[&item];
    }

    _destinationPositions[&item] = destinationItem.pos();

    newAnimation = new QGraphicsItemAnimation ( timeLine);
    newAnimation->setTimeLine ( timeLine );
    newAnimation->setItem ( &item );
    newAnimation->setPosAt ( 0, srcPos );
    newAnimation->setPosAt ( 1, destinationItem.pos() );
    newAnimation->deleteLater();
}


/**
 * start the animation on the graphicscene
 * @brief AnimatedGraphicsScene::startAnimation
 */
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

/**
 * If animation is ended, we need to cleanup
 * @brief AnimatedGraphicsScene::animationEnded
 */
void AnimatedGraphicsScene::animationEnded()
{
    // restart
    if ( _activeTimeLines.size() == 0)
    {
        _animationActive = false;
        _destinationPositions.clear();
        delete timeLine;

/*
        if(newAnimation != NULL && newAnimation->item() != NULL){
            newAnimation->item()->setZValue(0);
        }
  */
      eventLoop->exit();

        return;
    }
    QTimeLine * x = _activeTimeLines.dequeue();
    x->start();
}
