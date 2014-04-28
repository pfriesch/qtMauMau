#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <gameLogic/gamecontroller.h>

class Playground : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Playground( QObject * parent = 0 );
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    GameController gameController;

signals:
public slots:
};

#endif // PLAYGROUND_H
