#include "gamecontroller.h"

GameController::GameController(int currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    players.push_back(new HumanPlayer());
    for (int i = 0; i < playerCount; ++i) {
        players.push_back(new AIPlayer());
    }
}

void GameController::gameInit()
{
    connectPlayerSignals();
    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    vector<vector<Card> > playerCards;
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < 5; j++) {
            playerCards[i].push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    vector<int> otherPlayerCardCount;
    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.push_back(players[i]->getCardCount());
    }
    for (unsigned i = 0; i < players.size(); ++i) {

        players[i]->gameInit(playerCards[i], cardDepot.back(), otherPlayerCardCount);
    }
    players.at(currentPlayer)->doTurn();
    //    emit initPlayground(players[humanPlayer].getHand(), otherPlayerCardCount, cardDepot.back(), currentPlayer);
    //    emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
}

void GameController::playCard(int playerId, const Card& card, Card::cardSuit whishedSuit)
{
    if (currentPlayer == playerId) {
        players[currentPlayer]->dropCard(card);
        cardDepot.pushCard(card);
        nextTurn();
    }
}

void GameController::drawCard(int playerId)
{
    if (currentPlayer == playerId) {
        if (!currentPlayerDrewCard) {
            players[playerId]->reciveCard(cardStack.getLast(cardDepot));
            players[playerId]->playerDoTurn();
            currentPlayerDrewCard = true;
        }
    }
}

void GameController::doNothing(int playerId)
{
    if (currentPlayer == playerId) {
        if (!currentPlayerDrewCard) {
            players[playerId]->reciveCard(cardStack.getLast(cardDepot));
            players[playerId]->playerDoTurn();
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
