#include "AnimatedGraphicsScene.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QDebug>

AnimatedGraphicsScene::AnimatedGraphicsScene ( QObject * parent ) :
    QGraphicsScene ( parent )
    , _activeTimeLines (  )
    , _animationActive ( false )
{
}

void AnimatedGraphicsScene::startAnimation()
{
    //_activeTimeLine->start();

    if ( _animationActive == false )
    {
        _animationActive = true;
        _currentTimeLine->start();
    }
    else
    {
        _activeTimeLines.enqueue ( _currentTimeLine );
    }
    _currentTimeLine = NULL;
}

void AnimatedGraphicsScene::addPositionAnimation ( QGraphicsPixmapItem * item, QPointF destinationPoint )
{
    //    item->setPos ( destinationPoint );
    //    return;
    //srcPos = item->mapToScene( itemPos );
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

    QGraphicsItemAnimation * newAnimation = new QGraphicsItemAnimation ( _currentTimeLine );
    newAnimation->setTimeLine ( _currentTimeLine );
    newAnimation->setItem ( item );
    newAnimation->setPosAt ( 0, srcPos );
    newAnimation->setPosAt ( 1, destinationPoint );
}

void AnimatedGraphicsScene::prepareNewAnimation()
{
    //    if ( _activeTimeLine != NULL )
    //    {
    //        delete _activeTimeLine;
    //    }
    //Connect EventLoop
  //  connect(this, SIGNAL(finished()), &pause, SLOT(quit()));



    _currentTimeLine = new QTimeLine ( 500 );
    bool bOk = connect ( _currentTimeLine, SIGNAL ( finished() ), this, SLOT ( animationEnded() ) );
    Q_ASSERT ( bOk );
}

void AnimatedGraphicsScene::animationEnded()
{
    // restart
    if ( _activeTimeLines.isEmpty() )
    {
        _animationActive = false;
        _destinationPositions.clear();
        emit complete();
        return;
    }
    QTimeLine * x = _activeTimeLines.dequeue();
    qDebug() << "Starting time line: " << x;
    x->start();
}
