#include "playeritem.h"

PlayerItem::PlayerItem(direction dir, int cardCount, QPointF centerPoint, QObject* parent)
    : QObject(parent)
{
    this->centerPoint = centerPoint;
    this->playerDirection = dir;
    this->layoutKey = QString::number(playerDirection);

    switch (dir) {
    case direction::LEFT:
        specialCard = CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    case direction::RIGHT:
        specialCard = CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    case direction::TOP:
        specialCard = CardItem::specialCards::BLUE_VERTICAL;
        break;
    default:
        break;
    }

    this->measureLayout(cardCount);
    this->createCards(cardCount);
}

PlayerItem::PlayerItem(direction dir, QVector<Card> humanCards, QPointF centerPoint){
    this->centerPoint = centerPoint;
    this->playerDirection = dir;
    this->layoutKey = QString::number(playerDirection);
    this->measureLayout(humanCards.size());
    this->createHumanCards(humanCards);
}

PlayerItem::direction PlayerItem::getDirection(){
    return playerDirection;
}

void PlayerItem::createCards(int cardCount){
    for (int i = 0; i < cardCount; i++) {
        CardItem* card = new CardItem(specialCard);

        card->setPos(layout.value(layoutKey + "X"), layout.value(layoutKey + "Y"));

        if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
            layout.insert(layoutKey + "Y", layout.value(layoutKey + "Y") + cardGap);
        } else {
           layout.insert(layoutKey + "X", layout.value(layoutKey + "X") + cardGap);
        }

        cards->append(card);
    }
}


/**
 * Sry, but we need a own method for the human player, otherwise i go insane
 * @brief PlayerItem::createHumanCards
 * @param humanCards
 */
void PlayerItem::createHumanCards(QVector<Card> humanCards){
    for (int i = 0; i < humanCards.size(); i++) {
        CardItem* card = new CardItem(humanCards.at(i));
        card->setPos(layout.value(layoutKey + "X"), layout.value(layoutKey + "Y"));
        layout.insert(layoutKey + "X", layout.value(layoutKey + "X") + cardGap);

        cards->append(card);
    }
}

/**
 * Yes, this is measureLayout(), it calculates all the x and y points for every 3 player. I know it seems a little bit fucked up, and maybe we should
 * change it. But at this point I dont know how to make it better.
 * @brief PlayerItem::measureLayout
 * @param cardCount
 */
void PlayerItem::measureLayout(int cardCount)
{

    if (playerDirection == direction::LEFT) {
        int playerCardsWidth = (cardCount - 1 * cardGap) + (cardWidth - cardGap) - cardWidth;
        layout.insert(QString::number(direction::LEFT) + "X", cardWidth - 30);
        layout.insert(QString::number(direction::LEFT) + "Y", ((centerPoint.y() / 2) - (playerCardsWidth / 2)));
    }
    if (playerDirection == direction::TOP) {
        int playerCardsWidth = (cardCount * cardGap);
        layout.insert(QString::number(direction::TOP) + "X", ((centerPoint.x()) - (playerCardsWidth / 2) - cardGap));
        layout.insert(QString::number(direction::TOP) + "Y", cardHeight - 70);
    }
    if (playerDirection == direction::BOTTOM) {
        int playerCardsWidth = cardCount * cardGap;
        layout.insert(QString::number(direction::BOTTOM) + "X", ((centerPoint.x()) - (playerCardsWidth / 2)-cardGap));
        layout.insert(QString::number(direction::BOTTOM) + "Y", centerPoint.y()*2 - cardHeight - 30);
    }
    if (playerDirection == direction::RIGHT) {
        int playerCardsWidth = (cardCount - 1 * cardGap) + (cardWidth - cardGap) - cardWidth;
        layout.insert(QString::number(direction::RIGHT) + "X", centerPoint.x()*2-cardWidth - 30);
        layout.insert(QString::number(direction::RIGHT) + "Y", ((centerPoint.y()/2) - (playerCardsWidth / 2)));
    }
}

void PlayerItem::setPlayableCards(QVector<Card>* playableCards){
    for (int i = 0; i < playableCards->size(); ++i) {
        for (int j = 0; j < cards->size(); ++j) {
            if(playableCards->at(i) == cards->at(j)->getCard()){
                CardItem *cardItem = cards->at(j);
                cardItem->setPos(cardItem->getX(),cardItem->getY()-offsetPlayableCard);
                cardItem->getGraphicsItem()->setFlag(QGraphicsItem::ItemIsSelectable, true);

                /*QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
                effect->setColor(QColor(0,0,0,0));
                effect->setStrength(1);
                cards->at(j)->getGraphicsItem()->setGraphicsEffect(effect);
                */
            }
        }
    }
}

void PlayerItem::unsetPlayableCards(){
        for (int i = 0; i < cards->size(); ++i) {
                if( cards->at(i)->getGraphicsItem()->flags() == QGraphicsItem::ItemIsSelectable){
                    CardItem *cardItem = cards->at(i);
                    cardItem->setPos(cards->at(i)->getX(),cards->at(i)->getY()+offsetPlayableCard);
                    cardItem->getGraphicsItem()->setFlag(QGraphicsItem::ItemIsSelectable, false);
                }
            }
}


QVector<CardItem*>* PlayerItem::getCards()
{
    return cards;
}
