#include "carditem.h"
#include "settings.h"

/**
 * Constructor with Depot Card as Default
 * @brief CardItem::CardItem
 */
CardItem::CardItem()
    : specialCode(specialCards::DEPOT)
{
}

/**
 * Copy Constructor with special Card
 * @brief CardItem::CardItem
 * @param _card
 */
CardItem::CardItem(const Card& _card)
    : specialCode(CardItem::specialCards::NOT_USED)
    , card(_card)
{
    createImg();
}

/**
 * Create new Special Card Carditem
 * @brief CardItem::CardItem
 * @param _specialCode
 */
CardItem::CardItem(CardItem::specialCards _specialCode)
{
    specialCode = _specialCode;
}

/**
 * Copy Constructor
 * @brief CardItem::CardItem
 * @param _cardItem
 */
CardItem::CardItem(const CardItem& _cardItem)
    : graphicsItem(NULL)
    , x(_cardItem.getX())
    , y(_cardItem.getY())
    , card(_cardItem.getCard())
{
    if (graphicsItem != NULL) {
        graphicsItem->setPos(_cardItem.getX(), _cardItem.getY());
    }
    specialCode = _cardItem.getSpecialCode();
}

/**
 * overwritten = operator
 * @brief CardItem::operator =
 * @param _cardItem
 * @return
 */
CardItem& CardItem::operator=(const CardItem& _cardItem)
{
    card = _cardItem.getCard();
    x = _cardItem.getX();
    y = _cardItem.getY();
    specialCode = _cardItem.getSpecialCode();

    //neu erstellen des Bildes
    if(graphicsItem != NULL){
        delete graphicsItem;
        graphicsItem = NULL;
   }

    createImg();

    setPos(x, y);
    return *this;
}

/**
 * SetPosition for Card on Scene
 * @brief CardItem::setPos
 * @param _x
 * @param _y
 */
void CardItem::setPos(qreal _x, qreal _y)
{
    x = _x;
    y = _y;
    if (graphicsItem != NULL) {
        graphicsItem->setPos(x, y);
    }
}

/**
 * get primitive Logic Card
 * @brief CardItem::getCard
 * @return Card
 */
Card CardItem::getCard() const
{
    return card;
}

/**
 * deletes the Image
 * @brief CardItem::removeImg
 */
void CardItem::removeImg() const
{
    delete graphicsItem;
}

/**
 * @brief CardItem::getSpecialCode
 * @return
 */
CardItem::specialCards CardItem::getSpecialCode() const
{
    return specialCode;
}

/**
 * @brief CardItem::getGraphicsItem
 * @return
 */
QGraphicsPixmapItem* CardItem::getGraphicsItem() const
{
    return this->graphicsItem;
}

/**
 * creates Image for this card with this suit and value
 * @brief CardItem::createImg
 * @return
 */
QGraphicsPixmapItem* CardItem::createImg()
{

    deckNumber = Settings::getInstance()->getProperty("common/card_deck").toStdString();
    imgExtension = Settings::getInstance()->getProperty("common/card_img_extension").toStdString();

    if (graphicsItem == NULL) {

        std::string imgName("");
        if (specialCode != specialCards::NOT_USED) {
            imgName = getSpecialCardName();
        } else {
            imgName = getNormalCardName();
        }
        std::string fullImagePath("img/deck_" + deckNumber + "/" + imgName + imgExtension);

        graphicsItem = new QGraphicsPixmapItem(QPixmap(fullImagePath.c_str()));
        if (x != 0 && y != 0) {
            graphicsItem->setPos(x, y);
        }
    }
    return graphicsItem;
}

/**
 * Returns the specialCardName
 * @brief CardItem::getSpecialCardName
 * @return
 */
std::string CardItem::getSpecialCardName()
{
    std::string imgName("");
    switch (specialCode) {
    case CardItem::specialCards::DEPOT:
        imgName += "talon";
        break;
    case CardItem::specialCards::RED_HORIZONTAL:
        imgName += "rh";
        break;
    case CardItem::specialCards::RED_VERTICAL:
        imgName += "rv";
        break;
    case CardItem::specialCards::BLUE_HORIZONTAL:
        imgName += "bh";
        break;
    case CardItem::specialCards::BLUE_VERTICAL:
        imgName += "bv";
        break;
    default:
        break;
    }
    return imgName;
}

std::string CardItem::getNormalCardName()
{
    //because std::to_string() is bugged in some MinGW versions, a workaround
    std::stringstream ss;
    ss << card.getSuit() << card.getValue();
    std::string imgName(ss.str());

    return imgName;
}
/**
 * returns if this card is playable
 * @brief CardItem::getPlayable
 * @return
 */
bool CardItem::getPlayable() const
{
    return playable;
}

/**
 * Sets this card as playable
 * @brief CardItem::setPlayable
 * @param value
 */
void CardItem::setPlayable(bool value)
{
    playable = value;
}


qreal CardItem::getX() const
{
    return x;
}

qreal CardItem::getY() const
{
    return y;
}

CardItem::~CardItem()
{
    delete graphicsItem;
}
