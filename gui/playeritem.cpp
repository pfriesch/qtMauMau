#include "playeritem.h"

PlayerItem::PlayerItem(direction dir, short cardCount, QPointF centerPoint, QObject* parent)
    : QObject(parent)
{
    this->centerPoint = centerPoint;
    qDebug() << centerPoint;

    switch (dir) {
    case direction::LEFT:
        specialCard = CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    case direction::RIGHT:
        specialCard = CardItem::specialCards::BLUE_VERTICAL;
        break;
    case direction::TOP:
        specialCard = CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    default:
        break;
    }

    measureLayout(cardCount);

    for (int i = 0; i < cardCount; i++) {
        CardItem* card = new CardItem(specialCard);
        card->getGraphicsItem()->setPos(layout.value("PLAYER1_X"), layout.value("PLAYER1_Y"));
        layout.insert("PLAYER1_Y", layout.value("PLAYER1_Y") + verticalCardGap);
        cards.append(card);
    }
}

void PlayerItem::measureLayout(short cardCount)
{

    //The real center for a Card
    qreal sceneCenter_X = centerPoint.x() - cardWidth;
    qreal sceneCenter_Y = centerPoint.y() - cardHeight;

    int playerCardsWidth = cardCount * verticalCardGap;
    layout.insert("PLAYER1_X", cardWidth - 30);
    layout.insert("PLAYER1_Y", ((centerPoint.y()) - (playerCardsWidth / 2)));
}

QVector<CardItem*> PlayerItem::getCards()
{
    return cards;
}
