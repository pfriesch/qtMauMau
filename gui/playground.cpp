#include "gui\playground.h"

Playground::Playground(QObject* parent)
    : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

void Playground::startGame()
{

    QPointF sceneCenterPointRaw = this->sceneRect().center();
    qreal sceneCenter_X = sceneCenterPointRaw.x() - cardWidth;
    qreal sceneCenter_Y = sceneCenterPointRaw.y() - cardHeight;
    int depotX = sceneCenter_X + cardWidth + horizontalCardGap;

    stack = CardItem(CardItem::specialCards::RED_VERTICAL);
    stack.setPos(sceneCenter_X, sceneCenter_Y);

    depot = CardItem(CardItem::specialCards::DEPOT);
    depot.setPos(depotX, sceneCenter_Y);

    this->addItem(stack.createImg());
    this->addItem(depot.createImg());
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item != NULL) {

        //Clicked on Stack
        if (item == stack.createImg()) {
            qDebug("VIEW: Sende drawCard()");
            players.value(PlayerItem::direction::HUMAN)->unsetPlayableCards();
            emit drawCard();
        }
        //Clicked on Human Card
        PlayerItem* human = players.value(PlayerItem::direction::HUMAN);
        for (int j = 0; j < human->getCards()->size(); ++j) {
            CardItem* c = human->getCards()->at(j);
            if (c->createImg() == item && c->createImg()->isSelected()) {
                updateCard(depot, c->getCard());
                human->removeCard(c->getCard(), this);
                human->unsetPlayableCards();
                emit playCard(depot.getCard());
                qDebug("VIEW: sende playCard()");
            }
        }
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
// TODO: show starting player
void Playground::initPlayground(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer)
{
    createPlayer(humanPlayerCards, otherPlayerCardCount);
    updateCard(depot, topDepotCard);
}

void Playground::createPlayer(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount)
{
    QPointF center = this->sceneRect().center();
    PlayerItem* human = new PlayerItem(PlayerItem::direction::HUMAN, humanPlayerCards, center);
    players.insert(PlayerItem::direction::HUMAN, human);

    for (unsigned int i = 0; i < otherPlayerCardCount.size(); i++) {
        switch (i) {
        case 0: {
            PlayerItem* p1 = new PlayerItem(PlayerItem::direction::LEFT, otherPlayerCardCount[0], center);
            players.insert(PlayerItem::direction::LEFT, p1);
            break;
        }
        case 1: {
            PlayerItem* p2 = new PlayerItem(PlayerItem::direction::TOP, otherPlayerCardCount[1], center);
            players.insert(PlayerItem::direction::TOP, p2);
            break;
        }
        case 2: {
            PlayerItem* p3 = new PlayerItem(PlayerItem::direction::RIGHT, otherPlayerCardCount[2], center);
            players.insert(PlayerItem::direction::RIGHT, p3);
            break;
        }
        }
    }

    //Draw all Player Cards
    for (PlayerItem::direction dir : players.keys()) {
        PlayerItem* p = players.value(dir);
        for (int j = 0; j < p->getCards()->size(); ++j) {
            this->addItem(p->getCards()->at(j)->createImg());
        }
    }
}

void Playground::updateCard(CardItem& card, const Card &newCard)
{
    removeItem(card.createImg());
    card = CardItem(newCard);
    addItem(card.createImg());
    update(sceneRect());
}

void Playground::playerDoTurn(vector<Card> playableCards)
{
    players.value(PlayerItem::direction::HUMAN)->setPlayableCards(playableCards);
}

void Playground::playerPlaysCard(int player, const Card& playedCard)
{
    updateCard(depot, playedCard);

    switch (player) {
    case 1: {
        players.value(PlayerItem::direction::LEFT)->removeCard(playedCard, this);
        break;
    }
    case 2: {
        players.value(PlayerItem::direction::TOP)->removeCard(playedCard, this);
        break;
    }
    case 3: {
        players.value(PlayerItem::direction::RIGHT)->removeCard(playedCard, this);
        break;
    }
    }
}

void Playground::playerDrawsCard(short player)
{
    CardItem* cardItem = NULL;
    Card dummyCard;
    switch (player) {
    case 1: {
        cardItem = players.value(PlayerItem::direction::LEFT)->addCard(dummyCard);
        break;
    }
    case 2: {
        cardItem = players.value(PlayerItem::direction::TOP)->addCard(dummyCard);
        break;
    }
    case 3: {
        cardItem = players.value(PlayerItem::direction::RIGHT)->addCard(dummyCard);
        break;
    }
    default: break;
    }
    addItem(cardItem->createImg());
}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card)
{
    qDebug("VIEW: GET Signal - addPlayerCard");
    CardItem* cardItem = players.value(PlayerItem::direction::HUMAN)->addCard(card);
    addItem(cardItem->createImg());
}
