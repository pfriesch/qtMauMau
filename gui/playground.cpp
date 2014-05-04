#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include "gui\playground.h"

Playground::Playground(QObject* parent): QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    cardWidth = 71;
    cardHeight = 96;
    QBrush brush(img);
    this->setBackgroundBrush(brush);



    humanPlayerX = 0
            humanPlayerY = 0;

}

void Playground::startGame(){

    cardItems = new QVector< CardItem* >();
    QPointF centerPoint = this->sceneRect().center();
    qDebug() << centerPoint.x();
    CardItem *stack = new CardItem(CardItem::specialCards::RED_VERTICAL);
    QGraphicsPixmapItem *stackItem = stack->getGraphicsItem();
    stackItem->setPos(centerPoint.x()-stackItem->pixmap().width(),centerPoint.y()-stackItem->pixmap().height());
    cardItems->append(stack);
    this->addItem(stackItem);


    CardItem *talon = new CardItem(CardItem::specialCards::TALON);
    QGraphicsPixmapItem *talonItem = talon->getGraphicsItem();
    talonItem->setPos((centerPoint.x()-talonItem->pixmap().width())+cardWidth+20,centerPoint.y()-talonItem->pixmap().height());
    talonItem->setOpacity(0.7);
    cardItems->append(talon);
    this->addItem(talonItem);




    fakeInit();

    /*
    QGraphicsPixmapItem *stack = new QGraphicsPixmapItem(QPixmap("img/deck_1/b1fv.png"));


    centerPoint.setX(centerPoint.x()-stack->pixmap().width());
    centerPoint.setY(centerPoint.y()-stack->pixmap().height());
    stack->setPos(centerPoint);

    // Setup Depot
    QGraphicsPixmapItem *depot = new QGraphicsPixmapItem(QPixmap("img/deck_1/depot.png"));
    centerPoint = scene->sceneRect().center();

    centerPoint.setX((centerPoint.x()-stack->pixmap().width())+depot->pixmap().width()+10);
    centerPoint.setY(centerPoint.y()-stack->pixmap().height());
    depot->setPos(centerPoint);
    depot->setOpacity(0.6);


    scene->addItem(stack);
    scene->addItem(depot);
    */
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item == NULL) {
        // do stuff if not clicked on an item
    } else {

        //signal to GameController
        // QGraphicsScene::mousePressEvent(event); // this forwards the event to the item
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
// topDepotCard kann ja auch keine sein also NULL, vielleicht doch lieber POINTER!!! TODO
void Playground::initPlayground(QVector<Card> *humanPlayerCards, QVector<short> otherPlayerCardCount, Card *topDepotCard, short startingPlayer){
    qDebug() << "hier hier hier";
    int x = 0;
    for(int i=0;i < humanPlayerCards->size();i++){
        CardItem *card = new CardItem(humanPlayerCards->at(i));
        card->getGraphicsItem()->setPos((this->width()/2)+x,this->height()-cardHeight-20);
        x+= 20;
        this->addItem(card->getGraphicsItem());
    }

}


// bekomme alle Spielbaren Karten von Human player
void Playground::playerDoTurn(QVector<Card> *playableCards){

}

// Spieler spielt eine Karte und welche
void Playground::playerPlaysCard(short player, Card& playedCard){

}

// Spieler zieht eine Karte
void Playground::playerDrawsCard(short player, Card& card){

}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card){

}

void Playground::fakeInit(){
    QVector<short> otherPlayerCardCount = QVector<short>();
    for(int i=0;i<4;i++){
        otherPlayerCardCount += 5;
    }

    QVector<Card> *cards = new QVector<Card>();
    cards->append(Card(Card::cardSuit::CLUBS,Card::cardValue::ACE));
    cards->append(Card(Card::cardSuit::CLUBS,Card::cardValue::KING));
    cards->append(Card(Card::cardSuit::DIAMONDS,Card::cardValue::SEVEN));
    cards->append(Card(Card::cardSuit::HEARTS,Card::cardValue::TEN));
    cards->append(Card(Card::cardSuit::SPADES,Card::cardValue::QUEEN));
    short i = 2;
    Card *c = new Card(Card::cardSuit::SPADES,Card::cardValue::ACE);
    this->initPlayground(cards,otherPlayerCardCount,c,i);
}
