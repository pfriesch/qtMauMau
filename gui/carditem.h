#ifndef CARDITEM_H
#define CARDITEM_H

#include <QWidget>
#include <gameLogic/Card.h>
#include <QPixmap>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>
#include <QDebug>

class CardItem : public QWidget {
    Q_OBJECT
public:
    enum specialCards {
        TALON = 0,
        EMPTY_TALON = 1,
        BLUE_HORIZONTAL = 2,
        BLUE_VERTICAL = 3,
        RED_VERTICAL = 4,
        RED_HORIZONTAL = 5,
    };

    explicit CardItem(const Card _card, QWidget* parent = 0);
    CardItem(int specialCode);
    QGraphicsPixmapItem* getGraphicsItem();
    void setCard(const Card &card);
    Card& getCard();
    void setPos(qreal x, qreal y);
    qreal getX();
    qreal getY();

private:
    std::string getSpecialCardName();
    std::string getNormalCardName();

    std::string imgExtension;
    std::string deckNumber;
    bool specialCard = false;
    int specialCode;
    QGraphicsPixmapItem* graphicsItem = NULL;
    Card::cardSuit suit;
    Card::cardValue value;
    qreal x = 0;
    qreal y = 0;
    Card card;

signals:

public
slots:
};

#endif // CARDITEM_H
