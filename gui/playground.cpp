#include "gui\playground.h"

Playground::Playground(QObject* parent)
    : AnimatedGraphicsScene(parent)
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

    stack = (CardItem::specialCards::RED_VERTICAL);
    stack.setPos(sceneCenter_X, sceneCenter_Y);

    depot = CardItem(CardItem::specialCards::DEPOT);
    depot.setPos(depotX, sceneCenter_Y);

    this->addItem(stack.createImg());
    this->addItem(depot.createImg());
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem *item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
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

                // TODO: Sometimes the Jack isnt the card you can choose a color, we wanted it to let the player modify the action cards
                if(c->getCard().getValue() == Card::cardValue::JACK){
                    Card::cardSuit chosenColor(chooseColor());
                }

                updateDepotCard(*c, depot);
                human->removeCard(c->getCard());
                human->unsetPlayableCards();
                qDebug("VIEW: sende playCard()");
                human->setUnactive();
                emit playCard(depot.getCard());
            }
        }
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
// TODO: show starting player
void Playground::initPlayground(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer)
{
    createPlayer(humanPlayerCards, otherPlayerCardCount);
    CardItem depotCard(topDepotCard);
    updateDepotCard(depotCard, depot);
}

void Playground::createPlayer(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount)
{
    QPointF center = this->sceneRect().center();
    PlayerItem* human = new PlayerItem(PlayerItem::direction::HUMAN, humanPlayerCards, center, "Icke");
    players.insert(PlayerItem::direction::HUMAN, human);

    for (unsigned int i = 0; i < otherPlayerCardCount.size(); i++) {
        switch (i) {
        case 0: {
            PlayerItem* p1 = new PlayerItem(PlayerItem::direction::LEFT, otherPlayerCardCount[0], center, "Yoda");
            players.insert(PlayerItem::direction::LEFT, p1);
            break;
        }
        case 1: {
            PlayerItem* p2 = new PlayerItem(PlayerItem::direction::TOP, otherPlayerCardCount[1], center,"Anakin");
            players.insert(PlayerItem::direction::TOP, p2);
            break;
        }
        case 2: {
            PlayerItem* p3 = new PlayerItem(PlayerItem::direction::RIGHT, otherPlayerCardCount[2], center, "C3PO");
            players.insert(PlayerItem::direction::RIGHT, p3);
            break;
        }
        }
    }

    //Draw all Player Cards
    for (PlayerItem::direction dir : players.keys()) {
        PlayerItem* p = players.value(dir);
        for (int j = 0; j < p->getCards()->size(); ++j) {
            addItem(p->getCards()->at(j)->createImg());
        }
        addItem(p->getPlayername());
    }
}

void Playground::updateDepotCard(CardItem& fromCard, CardItem& toCard, bool withAnimation)
{
    qreal x = toCard.getX();
    qreal y = toCard.getY();

    if (withAnimation) {
        //TODO: Die QEventLoop geht glaub ich noch nicht richtig
        QEventLoop pause;
        prepareNewAnimation(pause);
        addPositionAnimation(fromCard.createImg(), toCard.createImg()->pos());
        startAnimation();
        pause.exec(QEventLoop::AllEvents);
    }

    removeItem(toCard.createImg());
    toCard = CardItem(fromCard.getCard());
    toCard.setPos(x, y);
    addItem(toCard.createImg());

    update(sceneRect());
}

void Playground::updatePlayerCard(CardItem& fromCard, CardItem& toCard, bool withAnimation)
{
    fromCard.setPos(stack.getX(),stack.getY());
    addItem(fromCard.createImg());

    qreal x = toCard.getX();
    qreal y = toCard.getY();

    if (withAnimation) {
        QEventLoop pause;
        prepareNewAnimation(pause);
        addPositionAnimation(fromCard.createImg(), toCard.createImg()->pos());
        startAnimation();
        pause.exec();
    }

    toCard = CardItem(fromCard);
    toCard.setPos(x, y);
    toCard.createImg()->setZValue(1);
    addItem(toCard.createImg());

    update(sceneRect());
}

void Playground::playerDoTurn(vector<Card> playableCards)
{
    players.value(PlayerItem::direction::HUMAN)->setActive();
    players.value(PlayerItem::direction::HUMAN)->setPlayableCards(playableCards);
}

void Playground::playerPlaysCard(int player, const Card& playedCard)
{
    qDebug("VIEW: GET Signal - playerPlaysCard");
    PlayerItem* p = NULL;
    switch (player) {
    case 1: {
        p = players.value(PlayerItem::direction::LEFT);
        break;
    }
    case 2: {
        p = players.value(PlayerItem::direction::TOP);
        break;
    }
    case 3: {
        p = players.value(PlayerItem::direction::RIGHT);
        break;
    }
    }
    p->setActive();
    //TODO: ist irgendwie falsch, er wird die gespielte Karte nie finden, da die View die Karten nicht kennt und nur SpecialCards also Blaue Hintergründe hält
    // für diesen Spieler, deshalb kommt einfach die last() Karte zurück
    CardItem *dummyCard = p->findCard(playedCard);
    CardItem _playedCard(playedCard);
    addItem(_playedCard.createImg());
    _playedCard.setPos(dummyCard->getX(), dummyCard->getY());
    p->removeCard(playedCard);
    updateDepotCard(_playedCard, depot);

    p->setUnactive();
}

/**
 * Other Player zieht eine Karte
 * @brief Playground::playerDrawsCard
 * @param player
 */
void Playground::playerDrawsCard(short player)
{
    qDebug("VIEW: GET Signal - playerDrawsCard");
    PlayerItem* p;

    switch (player) {
    case 1: {
        p = players.value(PlayerItem::direction::LEFT);
        break;
    }
    case 2: {
        p = players.value(PlayerItem::direction::TOP);
        break;
    }
    case 3: {
        p = players.value(PlayerItem::direction::RIGHT);
        break;
    }
    default:
        qFatal("Error in playerDrawsCard, bekomme anderen Wert als erwartet!");
        break;
    }

    p->setActive();

    Card dummyCard;
    CardItem *cardItem = p->addCard(dummyCard);
    CardItem fakeStack(p->getSpecialCard());
    updatePlayerCard(fakeStack, *cardItem);

    p->setUnactive();
}

/**
 * Human Spieler hat eine Karte gezogen
 * @brief Playground::addPlayerCard
 * @param card
 */
void Playground::addPlayerCard(const Card& card)
{
    qDebug("VIEW: GET Signal - addPlayerCard");
    CardItem* cardItem = players.value(PlayerItem::direction::HUMAN)->addCard(card);
    CardItem cardFromStack(card);
    updatePlayerCard(cardFromStack,*cardItem);
}

Card::cardSuit Playground::chooseColor(){

    ChooseColorDialog dialog;
    int p = dialog.exec();
    qDebug("Card Farbe: "+ dialog.result() +Card::cardSuit(dialog.result()));
    return Card::cardSuit(dialog.result());
}
