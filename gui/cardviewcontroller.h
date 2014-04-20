#ifndef CARDVIEWCONTROLLER_H
#define CARDVIEWCONTROLLER_H

#include <QObject>
#include <QGraphicsScene>

class CardViewController : public QObject
{
    Q_OBJECT
public:
    explicit CardViewController(QObject *parent = 0);
    void initGame(QGraphicsScene *scene);
signals:

public slots:

};

#endif // CARDVIEWCONTROLLER_H
