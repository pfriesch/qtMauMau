#include "gui/playground.h"

Playground::Playground(QObject* parent)
    : AnimatedGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

/**
 * Starts the game and initializes the Depot/Stack and so on
 * @brief Playground::startGame
 */
void Playground::startGame()
{
    history.write("Start new Game\n=====================");
    soundMgr.startSound();
    stack = (CardItem::specialCards::RED_VERTICAL);
    depot = CardItem(CardItem::specialCards::DEPOT);

    this->setDepotNStack();

    this->addItem(stack.createImg());
    this->addItem(depot.createImg());
    soundMgr.playBackgroundSong();
}

/**
 * Sets the position of Depot and Stack
 * @brief Playground::setDepotNStack
 */
void Playground::setDepotNStack()
{
    QPointF sceneCenterPointRaw = this->sceneRect().center();
    qreal sceneCenter_X = sceneCenterPointRaw.x() - cardWidth;
    qreal sceneCenter_Y = sceneCenterPointRaw.y() - cardHeight;
    int depotX = sceneCenter_X + cardWidth + horizontalCardGap;
    depot.setPos(depotX, sceneCenter_Y);
    stack.setPos(sceneCenter_X, sceneCenter_Y);
}

/**
 * MouseEvent for clicking on a humanCard or on the Stack
 * @brief Playground::mousePressEvent
 * @param event
 */
void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
        if (item != NULL) {

            //Clicked on Stack
            if (item == stack.createImg()) {
                players.value(PlayerItem::direction::HUMAN)->unsetPlayableCards();
                players.value(PlayerItem::direction::HUMAN)->setUnactive();
                emit drawCard();
            }
            //Clicked on Human Card
            PlayerItem* human = players.value(PlayerItem::direction::HUMAN);
            for (int j = 0; j < human->getCards()->size(); ++j) {
                CardItem* c = human->getCards()->at(j);
                if (c->createImg() == item && c->getPlayable()) {
                    history.write("You play a Card", c->getCard().getSuit(), c->getCard().getValue());
                    Card::cardSuit chosenColor = Card::NONE;
                    if (c->getCard().getValue() == wishSuitCard) {
                        chosenColor = chooseColor();
                    }
                    soundMgr.playCard();
                    updateDepotCard(*c, depot);
                    soundMgr.drawCard();
                    human->removeCard(c->getCard());
                    human->unsetPlayableCards();
                    human->setUnactive();
                    emit playCard(depot.getCard(), chosenColor);
                }
            }
        }
    }
}


/**
 * Get all Cards from HumanPlayer, with otherPlayerCardCount, with the topDepotCard and so on
 * @brief Playground::initPlayground
 * @param humanPlayerCards
 * @param otherPlayerCardCount
 * @param topDepotCard
 * @param _wishSuitCard
 * @param playerNames
 */
void Playground::initPlayground(const std::vector<Card> humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames)
{
    wishSuitCard = _wishSuitCard;
    createPlayer(humanPlayerCards, otherPlayerCardCount, playerNames);
    CardItem depotCard(topDepotCard);
    updateDepotCard(depotCard, depot);
}

/**
 * Creates the player for initialization
 * @brief Playground::createPlayer
 * @param humanPlayerCards
 * @param otherPlayerCardCount
 * @param playerNames
 */
void Playground::createPlayer(const std::vector<Card> humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames)
{
    QPointF center = this->sceneRect().center();
    PlayerItem* human = new PlayerItem(PlayerItem::direction::HUMAN, humanPlayerCards, center.x(), center.y(), QString(playerNames.at(0).c_str()));
    players.insert(PlayerItem::direction::HUMAN, human);

    for (unsigned int i = 0; i < otherPlayerCardCount.size(); i++) {
        switch (i) {
        case 1: {
            PlayerItem* p1 = new PlayerItem(PlayerItem::direction::LEFT, otherPlayerCardCount.at(PLAYER::Name::LEFT), center.x(), center.y(), QString(playerNames.at(1).c_str()), this);
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

/**
 * updates the Depot Card
 * @brief Playground::updateDepotCard
 * @param fromCard
 * @param toCard
 * @param withAnimation with Animation or without
 */
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

/**
 * updates the Player card with animation from stack to the playerhand
 * @brief Playground::updatePlayerCard
 * @param fromCard
 * @param toCard
 * @param withAnimation
 */
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
    if ((&toCard) != NULL) {
    }
    toCard = CardItem(fromCard);
    toCard.setPos(x, y);
    toCard.createImg()->setZValue(zValue);
    zValue++;
    addItem(toCard.createImg());

    update(sceneRect());
}

/**
 * Slot, the human player is on turn and have to select a Card, you get the wished suit and the playableCards
 * @brief Playground::playerDoTurn
 * @param playableCards
 * @param wishedSuit
 */
void Playground::playerDoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit)
{
    history.write("You have to play, your Cards are:", players.value(PlayerItem::direction::HUMAN)->getCards());
    players.value(PlayerItem::direction::HUMAN)->setActive(wishedSuit);
    players.value(PlayerItem::direction::HUMAN)->setPlayableCards(playableCards);
}

/**
 * An other player plays a card from his hand to the stack
 * @brief Playground::playerPlaysCard
 * @param player
 * @param playedCard
 */
void Playground::playerPlaysCard(PLAYER::Name player, const Card& playedCard)
{
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

    CardItem* dummyCard = p->findCard(playedCard, true);
    CardItem _playedCard(playedCard);
    history.write("another Player, plays a Card", _playedCard);
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
    history.write("Another Player draws a Card");
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
    history.write("You draw Card", card.getSuit(), card.getValue());
    CardItem* cardItem = players.value(PlayerItem::direction::HUMAN)->addCard(card);
    CardItem cardFromStack(card);
    soundMgr.playCard();
    updatePlayerCard(cardFromStack, *cardItem);
    if (cardItem)
        players.value(PlayerItem::direction::HUMAN)->rearrangePlayer(this->sceneRect().center().x(), this->sceneRect().center().y());
}

/**
 * Yea, a player one the game congratulations
 * @brief Playground::playerWon
 * @param _title
 */
void Playground::playerWon(std::string _title)
{
    history.write("WIIIN");
    history.write("GAME OVER\n===================\n");
    soundMgr.winnerSound();
    QMessageBox msgBox;
    msgBox.setText(QMessageBox::tr("Player ") + _title.c_str() + tr(" won!!"));
    msgBox.exec();
}

/**
 * show dialog for choosing color
 * @brief Playground::chooseColor
 * @return
 */
Card::cardSuit Playground::chooseColor()
{

    ChooseColorDialog dialog;
    return Card::cardSuit(dialog.exec());
}

/**
 * If we resize the scene, we have to rearrange all the players
 * @brief Playground::rearrangeLayout
 */
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

Playground::~Playground()
{
    for (CardItem* items : graphicalItems) {
        if (items != NULL)
            delete items;
    }

    for (PlayerItem* player : players) {
        if (player != NULL)
            delete player;
    }
}
