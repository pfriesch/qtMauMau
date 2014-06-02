#include "playeritem.h"

PlayerItem::PlayerItem(direction dir, int cardCount, QPointF centerPoint, QString _playername, QObject* parent)
    : QObject(parent)
{

    this->centerPoint = centerPoint;
    playerDirection = dir;
    specialCard = getSpecialCard();

    measureLayout(cardCount);
    createCards(cardCount);

    playername = new QGraphicsTextItem(_playername);
    playername->setScale(2);
    playername->setDefaultTextColor(QColor(255, 255, 255));
    playername->setPos(nameX, nameY);
}

/**
 * Own Constructor for the Human Player
 * @brief PlayerItem::PlayerItem
 * @param dir
 * @param humanCards
 * @param centerPoint
 * @param _playername
 */
PlayerItem::PlayerItem(direction dir, std::vector<Card> humanCards, QPointF centerPoint, QString _playername)
{
    this->centerPoint = centerPoint;
    playerDirection = dir;
    measureLayout(humanCards.size());
    createHumanCards(humanCards);

    playername = new QGraphicsTextItem(_playername);
    playername->setScale(2);
    playername->setDefaultTextColor(QColor(255, 255, 255));
    playername->setPos(nameX, nameY);
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
        nameX = x;
        nameY = y - 20;
    }
    if (playerDirection == direction::TOP) {
        int playerCardsWidth = (cardCount * cardGap);
        x = (centerPoint.x() - (playerCardsWidth / 2) - cardGap);
        y = cardHeight - 70;
        nameX = x - 70;
        nameY = y;
    }
    if (playerDirection == direction::HUMAN) {
        int playerCardsWidth = cardCount * cardGap;
        x = (centerPoint.x()) - (playerCardsWidth / 2) - cardGap;
        y = centerPoint.y() * 2 - cardHeight - borderMargin;
        nameX = x - 70;
        nameY = y - 60;
    }
    if (playerDirection == direction::RIGHT) {
        int playerCardsWidth = (cardCount - 1 * cardGap) + (cardWidth - cardGap) - cardWidth;
        x = centerPoint.x() * 2 - cardWidth - borderMargin;
        y = (centerPoint.y() / 2) - (playerCardsWidth / 2);
        nameX = x;
        nameY = y - 20;
    }
}

void PlayerItem::rearrangePlayer(QPointF centerPoint)
{
    this->centerPoint = centerPoint;
    this->measureLayout(this->getCards()->size());
    playername->setPos(nameX, nameY);
    for (int i = 0; i < this->getCards()->size(); ++i) {
        if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
            y += cardGap;
        } else {
            x += cardGap;
        }

        this->getCards()->at(i)->setPos(x, y);
    }
}

void PlayerItem::setPlayableCards(std::vector<Card> playableCards)
{
    for (unsigned int i = 0; i < playableCards.size(); ++i) {
        CardItem* cardItem = findCard(playableCards.at(i));
        cardItem->setPos(cardItem->getX(), cardItem->getY() - offsetPlayableCard);
        cardItem->getGraphicsItem()->setFlag(QGraphicsItem::ItemIsSelectable, true);
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

void PlayerItem::setActive()
{
    playername->setHtml("<p style='text-decoration:underline;font-style:oblique;'>" + playername->toPlainText() + "</p>");
}

void PlayerItem::setUnactive()
{
    playername->setHtml(playername->toPlainText());
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
    CardItem* cardItem = findCard(card);

    if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
        y -= cardGap;
    }
    if (playerDirection == direction::TOP) {
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

QGraphicsTextItem* PlayerItem::getPlayername()
{
    return playername;
}

PlayerItem::~PlayerItem()
{
    delete[] cards;
}
