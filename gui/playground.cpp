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
    soundMgr.startSound();
    stack = (CardItem::specialCards::RED_VERTICAL);
    depot = CardItem(CardItem::specialCards::DEPOT);

    this->setDepotNStack();

    this->addItem(stack.createImg());
    this->addItem(depot.createImg());
    soundMgr.playBackgroundSong();
}

void Playground::setDepotNStack()
{
    QPointF sceneCenterPointRaw = this->sceneRect().center();
    qreal sceneCenter_X = sceneCenterPointRaw.x() - cardWidth;
    qreal sceneCenter_Y = sceneCenterPointRaw.y() - cardHeight;
    int depotX = sceneCenter_X + cardWidth + horizontalCardGap;
    depot.setPos(depotX, sceneCenter_Y);
    stack.setPos(sceneCenter_X, sceneCenter_Y);
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
        if (item != NULL) {

            //Clicked on Stack
            if (item == stack.createImg()) {
                qDebug("VIEW: Sende drawCard()");
                players.value(PlayerItem::direction::HUMAN)->unsetPlayableCards();
                players.value(PlayerItem::direction::HUMAN)->setUnactive();
                emit drawCard();
            }
            //Clicked on Human Card
            PlayerItem* human = players.value(PlayerItem::direction::HUMAN);
            for (int j = 0; j < human->getCards()->size(); ++j) {
                CardItem* c = human->getCards()->at(j);
                if (c->createImg() == item && c->getPlayable()) {
                    Card::cardSuit chosenColor = Card::NONE;
                    if (c->getCard().getValue() == wishSuitCard) {
                        chosenColor = chooseColor();
                        qDebug() << "CHOOOSEN COLOR: " << chosenColor;
                    }
                    soundMgr.playCard();
                    updateDepotCard(*c, depot);
                    soundMgr.drawCard();
                    human->removeCard(c->getCard());
                    human->unsetPlayableCards();
                    qDebug("VIEW: sende playCard()");
                    human->setUnactive();
                    emit playCard(depot.getCard(), chosenColor);
                }
            }
        }
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
void Playground::initPlayground(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames)
{
    wishSuitCard = _wishSuitCard;
    createPlayer(humanPlayerCards, otherPlayerCardCount, playerNames);
    CardItem depotCard(topDepotCard);
    updateDepotCard(depotCard, depot);
}

void Playground::createPlayer(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames)
{
    QPointF center = this->sceneRect().center();
    PlayerItem* human = new PlayerItem(PlayerItem::direction::HUMAN, humanPlayerCards, center.x(), center.y(), QString(playerNames.at(0).c_str()));
    players.insert(PlayerItem::direction::HUMAN, human);

    for (unsigned int i = 0; i < otherPlayerCardCount.size(); i++) {
        switch (i) {
        case 1: {
            PlayerItem* p1 = new PlayerItem(PlayerItem::direction::LEFT, otherPlayerCardCount.at(PLAYER::Name::LEFT), center.x(), center.y(), QString(playerNames.at(1).c_str()));
            players.insert(PlayerItem::direction::LEFT, p1);
            break;
        }
        case 2: {
            PlayerItem* p2 = new PlayerItem(PlayerItem::direction::TOP, otherPlayerCardCount.at(PLAYER::Name::TOP), center.x(), center.y(), QString(playerNames.at(2).c_str()));
            players.insert(PlayerItem::direction::TOP, p2);
            break;
        }
        case 3: {
            PlayerItem* p3 = new PlayerItem(PlayerItem::direction::RIGHT, otherPlayerCardCount.at(PLAYER::Name::RIGHT), center.x(), center.y(), QString(playerNames.at(3).c_str()));
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
        QEventLoop pause;
        prepareNewAnimation(pause);
        addPositionAnimation(*fromCard.createImg(), *toCard.createImg());
        startAnimation();
        pause.exec(QEventLoop::AllEvents);
    }

    removeItem(toCard.createImg());
    toCard = CardItem(fromCard.getCard());
    toCard.setPos(x, y);
    toCard.createImg()->setZValue(zValue);
    zValue++;
    addItem(toCard.createImg());

    update(sceneRect());
}

void Playground::updatePlayerCard(CardItem& fromCard, CardItem& toCard, bool withAnimation)
{
    fromCard.setPos(stack.getX(), stack.getY());
    addItem(fromCard.createImg());

    qreal x = toCard.getX();
    qreal y = toCard.getY();

    if (withAnimation) {
        QEventLoop pause;
        prepareNewAnimation(pause);
        addPositionAnimation(*fromCard.createImg(), *toCard.createImg());
        startAnimation();
        pause.exec();
    }

    toCard = CardItem(fromCard);
    toCard.setPos(x, y);
    toCard.createImg()->setZValue(zValue);
    zValue++;
    addItem(toCard.createImg());

    update(sceneRect());
}

void Playground::playerDoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit)
{
    qDebug("Player do Turn; cards: ");
    for (unsigned i = 0; i < playableCards.size(); ++i) {
        qDebug() << playableCards[i].getSuit() << ":" << playableCards[i].getValue();
    }

    players.value(PlayerItem::direction::HUMAN)->setActive(wishedSuit);
    players.value(PlayerItem::direction::HUMAN)->setPlayableCards(playableCards);
}

void Playground::playerPlaysCard(PLAYER::Name player, const Card& playedCard)
{

    qDebug("VIEW: GET Signal - playerPlaysCard");
    PlayerItem* p = NULL;
    switch (player) {
    case PLAYER::Name::LEFT: {
        p = players.value(PlayerItem::direction::LEFT);
        break;
    }
    case PLAYER::Name::TOP: {
        p = players.value(PlayerItem::direction::TOP);
        break;
    }
    case PLAYER::Name::RIGHT: {
        p = players.value(PlayerItem::direction::RIGHT);
        break;
    }
    default:
        break;
    }
    p->setActive();
    //TODO: ist irgendwie falsch, er wird die gespielte Karte nie finden, da die View die Karten nicht kennt und nur SpecialCards also Blaue Hintergründe hält
    // für diesen Spieler, deshalb kommt einfach die last() Karte zurück
    CardItem* dummyCard = p->findCard(playedCard, true);
    CardItem _playedCard(playedCard);
    addItem(_playedCard.createImg());
    _playedCard.setPos(dummyCard->getX(), dummyCard->getY());
    p->removeCard(playedCard);
    soundMgr.playCard();
    updateDepotCard(_playedCard, depot);
    p->setUnactive();
    p->rearrangePlayer(this->sceneRect().center().x(), this->sceneRect().center().y());
}

/**
 * Other Player zieht eine Karte
 * @brief Playground::playerDrawsCard
 * @param player
 */
void Playground::playerDrawsCard(PLAYER::Name player)
{
    qDebug("VIEW: GET Signal - playerDrawsCard");
    PlayerItem* p;

    switch (player) {
    case PLAYER::Name::LEFT: {
        p = players.value(PlayerItem::direction::LEFT);
        break;
    }
    case PLAYER::Name::TOP: {
        p = players.value(PlayerItem::direction::TOP);
        break;
    }
    case PLAYER::Name::RIGHT: {
        p = players.value(PlayerItem::direction::RIGHT);
        break;
    }
    default:
        qFatal("Error in playerDrawsCard, shouldn't happen!");
        break;
    }

    p->setActive();

    Card dummyCard;
    CardItem* cardItem = p->addCard(dummyCard);
    CardItem fakeStack(p->getSpecialCard());
    soundMgr.playCard();
    updatePlayerCard(fakeStack, *cardItem);
    p->setUnactive();
    p->rearrangePlayer(this->sceneRect().center().x(), this->sceneRect().center().y());
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
    soundMgr.playCard();
    updatePlayerCard(cardFromStack, *cardItem);
    players.value(PlayerItem::direction::HUMAN)->rearrangePlayer(this->sceneRect().center().x(), this->sceneRect().center().y());
}

void Playground::playerWon(PLAYER::Name playerName)
{
    soundMgr.winnerSound();
    QMessageBox msgBox;
    msgBox.setText(QMessageBox::tr("Congratulations Player ") + playerName + " won!!");
    msgBox.exec();
}

Card::cardSuit Playground::chooseColor()
{

    ChooseColorDialog dialog;
    return Card::cardSuit(dialog.exec());
}

void Playground::rearrangeLayout()
{
    if (players.size() > 0) {
        QHash<PlayerItem::direction, PlayerItem*>::iterator i = players.begin();
        for (i = players.begin(); i != players.end(); ++i) {
            PlayerItem* p = players.value(i.key());
            p->rearrangePlayer(this->sceneRect().center().x(), this->sceneRect().center().y());
        }
        this->setDepotNStack();
    }
}
