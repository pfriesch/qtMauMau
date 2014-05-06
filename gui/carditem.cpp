#include "carditem.h"

CardItem::CardItem(const Card _card, QWidget* parent) : QWidget(parent)
{
    card = _card;
}

CardItem::CardItem(int specialCode)
{
    specialCard = true;
    this->specialCode = specialCode;
}

void CardItem::setPos(qreal x, qreal y){
    this->x = x;
    this->y = y;
    if(graphicsItem != NULL){
        graphicsItem->setPos(x,y);
    }
}

Card& CardItem::getCard(){
    return card;
}

QGraphicsPixmapItem* CardItem::getGraphicsItem()
{
    //TODO: make this variable, so we can use different card decks
    deckNumber = "1";
    imgExtension = ".png";

    if (graphicsItem == NULL) {

        std::string imgName("");
        if (specialCard) {
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
    case CardItem::specialCards::TALON:
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

qreal CardItem::getX(){
    return x;
}

qreal CardItem::getY(){
    return y;
}

void CardItem::setCard(const Card &_card){
    specialCard = false;
    card = _card;
    graphicsItem = NULL;
}
