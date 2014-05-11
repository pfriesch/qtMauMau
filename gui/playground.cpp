#include "gui\playground.h"

Playground::Playground(QObject* parent)
    : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

void Playground::measureLayout()
{
    //Center for the scene, but we need to include the card sizes
    QPointF sceneCenterPointRaw = this->sceneRect().center();
    //The real center for a Card
    qreal sceneCenter_X = sceneCenterPointRaw.x() - cardWidth;
    qreal sceneCenter_Y = sceneCenterPointRaw.y() - cardHeight;

    layout.insert("STACK_X", sceneCenter_X);
    layout.insert("STACK_Y", sceneCenter_Y);

    layout.insert("depot_X", sceneCenter_X + cardWidth + horizontalCardGap);
    layout.insert("depot_Y", sceneCenter_Y);
}

void Playground::startGame()
{

    measureLayout();

    stack = CardItem(CardItem::specialCards::RED_VERTICAL);
    stack.setPos(layout.value("STACK_X"), layout.value("STACK_Y"));

    depot = CardItem(CardItem::specialCards::DEPOT);
    depot.setPos(layout.value("depot_X"), layout.value("depot_Y"));

    this->addItem(stack.createImg());
    this->addItem(depot.createImg());
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item != NULL) {

        //Clicked on Stack
        if (item == stack.createImg()) {
            emit drawCard();
        }
        //Clicked on Human Card
        PlayerItem* human = players.value(PlayerItem::direction::HUMAN);
        for (int j = 0; j < human->getCards()->size(); ++j) {
            CardItem* c = human->getCards()->at(j);
            if (c->createImg() == item && c->createImg()->isSelected()) {
                removeItem(c->createImg());
                updateCard(depot, c->getCard());
                human->unsetPlayableCards();
                emit playCard(c->getCard());
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

void Playground::updateCard(CardItem& card, const Card newCard)
{
    removeItem(card.createImg());
    card.setCard(newCard);
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
}

// Spieler zieht eine Karte
/*void Playground::playerDrawsCard(short player, Card& card)
{
}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card)
{
}
*/
