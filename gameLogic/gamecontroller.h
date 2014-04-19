#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

class GameController : public QObject
{
  Q_OBJECT
public:
  explicit GameController(QObject *parent = 0);

signals:

public slots:

};

#endif // GAMECONTROLLER_H
