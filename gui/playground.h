#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Playground : public QGraphicsScene {
    Q_OBJECT
public:
    explicit Playground(QObject* parent = 0);
    void init();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
signals:

public
slots:
};

#endif // PLAYGROUND_H
