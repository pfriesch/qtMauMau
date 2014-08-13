#include "carditem.h"
#include "settings.h"

CardItem::CardItem()
    : specialCode(specialCards::DEPOT)
{
}

CardItem::CardItem(const Card& _card)
    : specialCode(CardItem::specialCards::NOT_USED)
    , card(_card)
{
    createImg();
}

CardItem::CardItem(CardItem::specialCards _specialCode)
{
    specialCode = _specialCode;
}

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

void CardItem::setPos(qreal _x, qreal _y)
{
    x = _x;
    y = _y;
    if (graphicsItem != NULL) {
        graphicsItem->setPos(x, y);
    }
}

Card CardItem::getCard() const
{
    return card;
}

void CardItem::removeImg() const
{
    delete graphicsItem;
}

CardItem::specialCards CardItem::getSpecialCode() const
{
    return specialCode;
}

QGraphicsPixmapItem* CardItem::getGraphicsItem() const
{
    return this->graphicsItem;
}

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
bool CardItem::getPlayable() const
{
    return playable;
}

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
