#ifndef ANIMATEDGRAPHICSSCENE_H
#define ANIMATEDGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QQueue>
#include <QMap>
#include <QEventLoop>

class QTimeLine;

class AnimatedGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AnimatedGraphicsScene ( QObject * parent = 0 );

    void addPositionAnimation ( QGraphicsPixmapItem *item , QPointF destinationPoint );
signals:
    void complete();
public slots:
    void startAnimation();
    void prepareNewAnimation();
    void animationEnded();
protected:
    QQueue<QTimeLine *> _activeTimeLines;
    QTimeLine * _currentTimeLine;
    bool _animationActive;

    QMap<QGraphicsItem *, QPointF> _destinationPositions;
};

#endif // ANIMATEDGRAPHICSSCENE_H
