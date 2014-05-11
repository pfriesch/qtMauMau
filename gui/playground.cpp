#include "gui\playground.h"

Playground::Playground(QObject* parent) : QGraphicsScene(parent)
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

    layout.insert("TALON_X", sceneCenter_X + cardWidth + horizontalCardGap);
    layout.insert("TALON_Y", sceneCenter_Y);
}

void Playground::startGame()
{

    measureLayout();

    stack = CardItem(CardItem::specialCards::RED_VERTICAL);
    stack.setPos(layout.value("STACK_X"), layout.value("STACK_Y"));
    this->addItem(stack.createImg());

    talon = CardItem(CardItem::specialCards::TALON);
    talon.setPos(layout.value("TALON_X"), layout.value("TALON_Y"));
    this->addItem(talon.createImg());
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item == NULL) {
        // do stuff if not clicked on an item, probably do nothing
    } else {
        for (int i = 0; i < players.size(); ++i) {
            PlayerItem *p = players.at(i);
            if(p->getDirection() == PlayerItem::direction::BOTTOM){
                for (int j = 0; j < p->getCards()->size(); ++j) {
                    CardItem *c = p->getCards()->at(j);
                    if(c->createImg() == item && c->createImg()->isSelected()){
                        removeItem(c->createImg());
                        updateCard(talon,c->getCard());
                        players.at(0)->unsetPlayableCards();
                        /// SIGNAL, DAS SPIELER GESPIELT HAT
                    }
                }
            }
        }
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
// TODO: show starting player
void Playground::initPlayground(const vector<Card>& humanPlayerCards, vector<int> otherPlayerCardCount, const Card& topDepotCard, int startingPlayer)
{
    PlayerItem* human = new PlayerItem(PlayerItem::direction::BOTTOM, humanPlayerCards, this->sceneRect().center());
    PlayerItem* p1 = new PlayerItem(PlayerItem::direction::LEFT, otherPlayerCardCount[0], this->sceneRect().center());
    PlayerItem* p2 = new PlayerItem(PlayerItem::direction::TOP, otherPlayerCardCount[1], this->sceneRect().center());
    PlayerItem* p3 = new PlayerItem(PlayerItem::direction::RIGHT, otherPlayerCardCount[2], this->sceneRect().center());

    players.append(human);
    players.append(p1);
    players.append(p2);
    players.append(p3);

    updateCard(talon,topDepotCard);

    // set playercards for every player
    for (int i = 0; i < players.size(); ++i) {
        PlayerItem* p(players.at(i));
        for (int j = 0; j < p->getCards()->size(); ++j) {
            this->addItem(p->getCards()->at(j)->createImg());
        }
    }

}

void Playground::updateCard(CardItem& card,const Card newCard){
    removeItem(card.createImg());
    card.setCard(newCard);
    addItem(card.createImg());
    update(sceneRect());
}



void Playground::playerDoTurn(vector<Card> playableCards)
{
    players.at(0)->setPlayableCards(playableCards);
}

void Playground::playerPlaysCard(int player, Card& playedCard)
{
}

// Spieler zieht eine Karte
/*void Playground::playerDrawsCard(short player, Card& card)
{
}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card)
{
}

/**
  * That are allllll fake methods
  *
 * @brief Playground::fakeInit

void Playground::fakeInit()
{
    QVector<short> otherPlayerCardCount = QVector<short>();
    for (int i = 0; i < 4; i++) {
        otherPlayerCardCount += 5;
    }

    QVector<Card>* cards = new QVector<Card>();
    cards->append(Card(Card::cardSuit::CLUBS, Card::cardValue::ACE));
    cards->append(Card(Card::cardSuit::CLUBS, Card::cardValue::KING));
    cards->append(Card(Card::cardSuit::DIAMONDS, Card::cardValue::SEVEN));
    cards->append(Card(Card::cardSuit::HEARTS, Card::cardValue::TEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));

    short i = 2;
    Card c(Card::cardSuit::SPADES, Card::cardValue::ACE);
    this->initPlayground(cards, otherPlayerCardCount, c, i);
}
*/
