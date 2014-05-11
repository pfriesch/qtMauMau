#include "carditem.h"

CardItem::CardItem() : specialCode(specialCards::DEPOT){

}

CardItem::CardItem(const Card& _card) : specialCode(CardItem::specialCards::NOT_USED),graphicsItem(NULL),card(_card)
{
}

CardItem::CardItem(CardItem::specialCards _specialCode)
{
    specialCode = _specialCode;
}

CardItem::CardItem(const CardItem& _cardItem): x(_cardItem.getX()), y(_cardItem.getY())
{
    specialCode = _cardItem.getSpecialCode();
    if(_cardItem.getGraphicsItem() != NULL){
        graphicsItem = NULL;
    }
}

CardItem& CardItem::operator= (const CardItem &_cardItem){
        card = _cardItem.getCard();
        specialCode = _cardItem.getSpecialCode();
        graphicsItem = NULL;
        return *this;
}

void CardItem::setPos(qreal _x, qreal _y){
    x = _x;
    y = _y;
    if(graphicsItem != NULL){
        graphicsItem->setPos(x,y);
    }
}

Card CardItem::getCard() const{
    return card;
}

void CardItem::removeImg() const{
    delete graphicsItem;
}

CardItem::specialCards CardItem::getSpecialCode() const{
    return specialCode;
}

QGraphicsPixmapItem* CardItem::getGraphicsItem() const{
    return this->graphicsItem;
}

QGraphicsPixmapItem* CardItem::createImg()
{
    //TODO: make this variable, so we can use different card decks
    deckNumber = "1";
    imgExtension = ".png";

    if (graphicsItem == NULL) {

        std::string imgName("");
        if (specialCode != specialCards::NOT_USED) {
            imgName = getSpecialCardName();
        } else {
            imgName = getNormalCardName();
        }
        std::string fullImagePath("img/deck_" + deckNumber + "/" + imgName + imgExtension);

        graphicsItem = new QGraphicsPixmapItem(QPixmap(fullImagePath.c_str()));
        if(x != 0 && y != 0){
            graphicsItem->setPos(x,y);
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
    std::string imgName("");

    //Set the Name for the color
    switch (card.getSuit()) {
    case Card::cardSuit::HEARTS:
        imgName += "h";
        break;
    case Card::cardSuit::DIAMONDS:
        imgName += "d";
        break;
    case Card::cardSuit::CLUBS:
        imgName += "c";
        break;
    case Card::cardSuit::SPADES:
        imgName += "s";
        break;
    default:
        break;
    }

    //Everything over 4 is a Picture (Jack,Queen,King,...)
    if (card.getValue() > 4) {
        switch (card.getValue()) {
        case Card::cardValue::JACK:
            imgName += "j";
            break;
        case Card::cardValue::QUEEN:
            imgName += "q";
            break;
        case Card::cardValue::KING:
            imgName += "k";
            break;
        case Card::cardValue::ACE:
            imgName += "a";
            break;
        default:
            break;
        }
    } else {
        //because std::to_string() is bugged in some MinGW versions, a workaround
        std::stringstream ss;
        ss << card.getValue();
        imgName += ss.str();
    }
    return imgName;
}

qreal CardItem::getX() const{
    return x;
}

qreal CardItem::getY() const{
    return y;
}

CardItem::~CardItem(){
    delete graphicsItem;
}

/*
void CardItem::setCard(const Card &_card){
    specialCode = specialCards::NOT_USED;
    card = _card;
    graphicsItem = NULL;
}*/
