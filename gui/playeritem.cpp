#include "playeritem.h"

PlayerItem::PlayerItem(direction dir, int cardCount, QPointF centerPoint, QObject* parent)
    : QObject(parent)
{
    this->centerPoint = centerPoint;
    playerDirection = dir;
    specialCard = getSpecialCard();

    measureLayout(cardCount);
    createCards(cardCount);
}

PlayerItem::PlayerItem(direction dir, std::vector<Card> humanCards, QPointF centerPoint)
{
    this->centerPoint = centerPoint;
    this->playerDirection = dir;
    this->measureLayout(humanCards.size());
    this->createHumanCards(humanCards);
}

PlayerItem::direction PlayerItem::getDirection()
{
    return playerDirection;
}

void PlayerItem::createCards(int cardCount)
{
    for (int i = 0; i < cardCount; i++) {
        //This card is just a dummy
        const Card card;
        addCard(card);
    }
}

/**
 * Sry, but we need a own method for the human player, otherwise i go insane
 * @brief PlayerItem::createHumanCards
 * @param humanCards
 */
void PlayerItem::createHumanCards(std::vector<Card> humanCards)
{
    for (unsigned int i = 0; i < humanCards.size(); i++) {
        addCard(humanCards.at(i));
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
        x = cardWidth - borderMargin;
        y = (centerPoint.y() / 2) - (playerCardsWidth / 2);
    }
    if (playerDirection == direction::TOP) {
        int playerCardsWidth = (cardCount * cardGap);
        x = (centerPoint.x() - (playerCardsWidth / 2) - cardGap);
        y = cardHeight - 70;
    }
    if (playerDirection == direction::HUMAN) {
        int playerCardsWidth = cardCount * cardGap;
        x = (centerPoint.x()) - (playerCardsWidth / 2) - cardGap;
        y = centerPoint.y() * 2 - cardHeight - borderMargin;
    }
    if (playerDirection == direction::RIGHT) {
        int playerCardsWidth = (cardCount - 1 * cardGap) + (cardWidth - cardGap) - cardWidth;
        x = centerPoint.x() * 2 - cardWidth - borderMargin;
        y = (centerPoint.y() / 2) - (playerCardsWidth / 2);
    }
}

void PlayerItem::setPlayableCards(std::vector<Card> playableCards)
{
    for (unsigned int i = 0; i < playableCards.size(); ++i) {
        CardItem* cardItem = findCard(playableCards.at(i));
        cardItem->setPos(cardItem->getX(), cardItem->getY() - offsetPlayableCard);
        cardItem->getGraphicsItem()->setFlag(QGraphicsItem::ItemIsSelectable, true);

        /*QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
                effect->setColor(QColor(0,0,0,0));
                effect->setStrength(1);
                cards->at(j)->getGraphicsItem()->setGraphicsEffect(effect);
                */
    }
}

void PlayerItem::unsetPlayableCards()
{
    for (int i = 0; i < cards->size(); ++i) {
        if (cards->at(i)->getGraphicsItem()->flags() == QGraphicsItem::ItemIsSelectable) {
            CardItem* cardItem = cards->at(i);
            cardItem->setPos(cards->at(i)->getX(), cards->at(i)->getY() + offsetPlayableCard);
            cardItem->getGraphicsItem()->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    }
}

CardItem* PlayerItem::addCard(const Card& card)
{
    if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
        y += cardGap;
    } else {
        x += cardGap;
    }

    CardItem* cardItem = NULL;
    if (this->playerDirection == PlayerItem::direction::HUMAN) {
        cardItem = new CardItem(card);
    } else {
        cardItem = new CardItem(getSpecialCard());
    }
    cardItem->setPos(x, y);

    cards->append(cardItem);
    return cardItem;
}

void PlayerItem::removeCard(const Card& card)
{
    CardItem *cardItem = findCard(card);

    if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
        y -= cardGap;
    } if(playerDirection == direction::TOP) {
        x -= cardGap;
    }

    cards->remove(cards->indexOf(cardItem));
    delete cardItem;
}

CardItem* PlayerItem::findCard(const Card& card)
{
    for (int i = 0; i < cards->size(); ++i) {
        if (card == cards->at(i)->getCard()) {
            return cards->at(i);
        }
    }
    return cards->last();
}

CardItem::specialCards PlayerItem::getSpecialCard()
{
    switch (playerDirection) {
    case PlayerItem::direction::LEFT:
        return CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    case PlayerItem::direction::RIGHT:
        return CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    case PlayerItem::direction::TOP:
        return CardItem::specialCards::BLUE_VERTICAL;
        break;
    default:
        return CardItem::specialCards::BLUE_HORIZONTAL;
        break;
    }
}

QVector<CardItem*>* PlayerItem::getCards()
{
    return cards;
}

PlayerItem::~PlayerItem(){
    delete[] cards;
}
