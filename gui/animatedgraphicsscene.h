#ifndef ANIMATEDGRAPHICSSCENE_H
#define ANIMATEDGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QQueue>
#include <QMap>
#include <QEventLoop>
#include <QGraphicsItemAnimation>
#include <QEventLoop>

class QTimeLine;

class AnimatedGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AnimatedGraphicsScene ( QObject * parent = 0 );

    void addPositionAnimation ( QGraphicsPixmapItem &item , QGraphicsPixmapItem &destinationItem );
signals:
    void complete();
public slots:
    void startAnimation();
    void prepareNewAnimation(QEventLoop &loop);
    void animationEnded();
protected:
    QQueue<QTimeLine *> _activeTimeLines;
    QTimeLine *timeLine;
    bool _animationActive;
    QGraphicsItemAnimation *newAnimation = NULL;
    QEventLoop *eventLoop;

    QMap<QGraphicsItem*, QPointF> _destinationPositions;
};

#endif // ANIMATEDGRAPHICSSCENE_H
