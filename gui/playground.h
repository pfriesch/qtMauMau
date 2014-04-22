#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>

class Playground : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Playground( QObject * parent = 0 );
    void init();
};

#endif // PLAYGROUND_H
