#include "playeritem.h"

/**
 * Constructor of Playeritem
 * @brief PlayerItem::PlayerItem
 * @param dir direction of Player
 * @param cardCount how many cards have this player
 * @param xCenter where is the scene centerX
 * @param yCenter where is he scene centerY
 * @param _playername Sets the playername
 * @param parent
 */
PlayerItem::PlayerItem(direction dir, int cardCount, int xCenter, int yCenter, QString _playername, QObject* parent): QObject(parent)
{

    this->xCenter = xCenter;
    this->yCenter = yCenter;
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
 * @param dir direction
 * @param humanCards set human Cards
 * @param centerPoint set the Center Point x and y
 * @param _playername set the Playername
 */
PlayerItem::PlayerItem(direction dir, std::vector<Card> humanCards, int xCenter, int yCenter, QString _playername)
{
    this->xCenter = xCenter;
    this->yCenter = yCenter;
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

/**
 * create Cards for this player
 * @brief PlayerItem::createCards
 * @param cardCount how many cards you want create
 */
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
 * @param humanCards give the humand cards pls
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
        y = (yCenter / 2) - (playerCardsWidth / 2);
        nameX = x;
        nameY = y - 20;
    }
    if (playerDirection == direction::TOP) {
        int playerCardsWidth = (cardCount * cardGap);
        x = (xCenter - (playerCardsWidth / 2) - cardGap);
        y = cardHeight - 70;
        nameX = x - 120;
        nameY = y;
    }
    if (playerDirection == direction::HUMAN) {
        int playerCardsWidth = cardCount * cardGap;
        x = (xCenter) - (playerCardsWidth / 2) - cardGap;
        y = yCenter * 2 - cardHeight - borderMargin;
        nameX = x - 70;
        nameY = y - 60;
    }
    if (playerDirection == direction::RIGHT) {
        int playerCardsWidth = (cardCount - 1 * cardGap) + (cardWidth - cardGap) - cardWidth;
        x = xCenter * 2 - cardWidth - borderMargin;
        y = (yCenter / 2) - (playerCardsWidth / 2);
        nameX = x;
        nameY = y - 20;
    }
}

/**
 * rearrange this player on this scene
 * @brief PlayerItem::rearrangePlayer
 * @param xCenter give the xcenter of this scene
 * @param yCenter give the ycenter of this scene
 */
void PlayerItem::rearrangePlayer(int xCenter, int yCenter)
{
    this->xCenter = xCenter;
    this->yCenter = yCenter;
    this->measureLayout(this->getCards()->size());

    playername->setPos(nameX, nameY);
    for (int i = 0; i < this->getCards()->size(); ++i) {
        if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
            y += cardGap;
        } else {
            x += cardGap;
        }
        if(this->getCards()->at(i)->getPlayable()){
            std::vector<Card> v;
            this->getCards()->at(i)->setPos(x, y);
            v.push_back(this->getCards()->at(i)->getCard());
            setPlayableCards(v);
        }
        else{
            this->getCards()->at(i)->setPos(x, y);
        }
    }
}

/**
 * Sets the Playable Cards for this player
 * @brief PlayerItem::setPlayableCards
 * @param playableCards
 */
void PlayerItem::setPlayableCards(std::vector<Card> playableCards)
{
    for (unsigned int i = 0; i < playableCards.size(); ++i) {
        CardItem *cardItem = findCard(playableCards.at(i));
        cardItem->setPos(cardItem->getX(), cardItem->getY() - offsetPlayableCard);
        cardItem->setPlayable(true);
    }
}

/**
 * unsets the Playable cards for this player
 * @brief PlayerItem::unsetPlayableCards
 */
void PlayerItem::unsetPlayableCards()
{
    for (int i = 0; i < cards->size(); ++i) {
        if (cards->at(i)->getPlayable()) {
            CardItem* cardItem = cards->at(i);
            cardItem->setPos(cardItem->getX(), cardItem->getY() + offsetPlayableCard);
            cardItem->setPlayable(false);
        }
    }
}

/**
 * Is this player in turn
 * @brief PlayerItem::setActive
 * @param wishSuitCard what is the whised suit?
 */
void PlayerItem::setActive(Card::cardSuit wishSuitCard)
{
    switch(wishSuitCard){
    case Card::cardSuit::HEARTS: wish = "♥"; break;
    case Card::cardSuit::DIAMONDS: wish = "♦"; break;
    case Card::cardSuit::CLUBS: wish = "♣"; break;
    case Card::cardSuit::SPADES: wish = "♠"; break;
    default: wish = ""; break;
    }

    playername->setHtml("<p style='text-decoration:underline;font-style:oblique;'>" + playername->toPlainText()+" "+wish+"</p>");
}

/**
 * Set this player Inactive
 * @brief PlayerItem::setUnactive
 */
void PlayerItem::setUnactive()
{
    playername->setHtml(playername->toHtml().replace(wish,""));
    playername->setHtml(playername->toPlainText());
}

/**
 * Add a Card for this player
 * @brief PlayerItem::addCard
 * @param card
 * @return CardItem
 */
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

/**
 * remove a Player Card
 * @brief PlayerItem::removeCard
 * @param card what card do you want remove
 */
void PlayerItem::removeCard(const Card& card)
{
    CardItem* cardItem = findCard(card,true);

    if (playerDirection == direction::LEFT || playerDirection == direction::RIGHT) {
        y -= cardGap;
    }
    if (playerDirection == direction::TOP) {
        x -= cardGap;
    }

    cards->remove(cards->indexOf(cardItem));
    delete cardItem;
}

/**
 * Find card in playerhand
 * @brief PlayerItem::findCard
 * @param card
 * @param returnLastCard
 * @return
 */
CardItem* PlayerItem::findCard(const Card& card, bool returnLastCard)
{
    for (int i = 0; i < cards->size(); ++i) {
        if (card == cards->at(i)->getCard()) {
            return cards->at(i);
        }
    }
    if(returnLastCard){
        qDebug("Couldnt find Card, return last");
        return cards->last();
    }
    return NULL;
}

/**
 * @brief PlayerItem::getSpecialCard
 * @return
 */
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
    if(cards != NULL){
    for(int i = 0; i < cards->size();i++){
        if(cards->at(i) != NULL)
        delete cards->at(i);
    }
    delete cards;
    }

    if(playername != NULL)
        delete playername;
}
