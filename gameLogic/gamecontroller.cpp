#include "gamecontroller.h"

GameController::GameController(int currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    players.push_back(new HumanPlayer(0));
    for (int i = 1; i < playerCount; ++i) {
        players.push_back(new AIPlayer(i));
    }
}

void GameController::gameInit()
{
    connectPlayerSignals();
    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    std::vector<std::vector<Card> > *playerCards = new std::vector<std::vector<Card> >;
    for (int i = 0; i < playerCount; i++) {
        playerCards->push_back(std::vector<Card>());
        for (int j = 0; j < 5; j++) {
            playerCards->at(i).push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    std::vector<int> *otherPlayerCardCount = new std::vector<int>;
    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount->push_back(players[i]->getCardCount());
    }
    for (unsigned i = 0; i < players.size(); ++i) {

        players[i]->gameInit(playerCards->at(i), cardDepot.back(), *otherPlayerCardCount, currentPlayer);
    }
  //  players.at(currentPlayer)->doTurn();
}

HumanPlayer* GameController::getHumanPlayer()
{
    HumanPlayer* player = qobject_cast<HumanPlayer*>(players[0]);
    qDebug() << "";
    return player;
}

void GameController::playCard(int playerId, const Card& card, Card::cardSuit whishedSuit)
{
    if (currentPlayer == playerId) {
        cardDepot.pushCard(card);
        nextTurn();
    }
}

void GameController::drawCard(int playerId)
{
    if (currentPlayer == playerId) {
        if (!currentPlayerDrewCard) {
            players[playerId]->reciveCard(cardStack.getLast(cardDepot));
            players[playerId]->doTurn();
            currentPlayerDrewCard = true;
        }
    }
}

void GameController::doNothing(int playerId)
{
    if (currentPlayer == playerId) {
        if (!currentPlayerDrewCard) {
            players[playerId]->reciveCard(cardStack.getLast(cardDepot));
            players[playerId]->doTurn();
            currentPlayerDrewCard = true;
        } else {
            nextTurn();
        }
    }
}

void GameController::connectPlayerSignals()
{
    for (int i = 0; i < playerCount; ++i) {
        QObject::connect(players[i], &Player::playCard, this, &GameController::playCard);
        QObject::connect(players[i], &Player::drawCard, this, &GameController::drawCard);
        QObject::connect(players[i], &Player::doNothing, this, &GameController::doNothing);
        QObject::connect(this, &GameController::otherPlaysCard, players[i], &Player::otherPlaysCard);
        QObject::connect(this, &GameController::otherDrawsCard, players[i], &Player::otherDrawsCard);
    }
}

void GameController::nextTurn()
{
    setFlags(cardDepot.back());
    qDebug() << "Next Payer: " << currentPlayer;
    players[currentPlayer]->doTurn();
}

void GameController::setFlags(const Card& card)
{
    currentPlayerDrewCard = false;
    skipNextPlayer = false;

    if (card.getValue() == changeDirectCard) {
        if (changedDirection == true) {
            changedDirection = false;
        } else {
            changedDirection = true;
        }
    } else if (card.getValue() == skipNextCard) {
        skipNextPlayer = true;
    } else if (card.getValue() == wishSuitCard) {
        //TODO get wished suit
    } else if (card.getValue() == draw2xCard) {
        //TODO set draw 2
    }

    setNextPlayer();
    if (skipNextPlayer) {
        setNextPlayer();
    }

    //    bool draw2x = false;
    //    int draw2xCount = 0;

    //    //special cards
    //    bool withDraw2xCard = true;
    //    Card::cardValue draw2xCard = Card::SEVEN;
    //    bool withWishedSuit = true;
    //    Card::cardValue wishSuit = Card::JACK;
}

void GameController::setNextPlayer()
{
    if (changedDirection) {
        if (currentPlayer > 0) {
            currentPlayer--;
        } else {
            currentPlayer = playerCount - 1;
        }
    } else {
        if (currentPlayer < playerCount - 1) {
            currentPlayer++;
        } else {
            currentPlayer = 0;
        }
    }
}
