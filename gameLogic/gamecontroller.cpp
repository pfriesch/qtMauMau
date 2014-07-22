#include "gamecontroller.h"
#include "gamecontrollerproxy.h"
#include "humanplayer.h"
#include "aiplayer.h"

#include <QDebug>

GameController::GameController(playerName currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }

    players.push_back(new HumanPlayer(BOTTOM, GameControllerProxy(this, BOTTOM)));
    for (int i = 1; i < playerCount; ++i) {
        players.push_back(new AIPlayer(playerName(i), GameControllerProxy(this, playerName(i))));
    }
}

void GameController::gameInit()
{

    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    std::vector<std::vector<Card> >* playerCards = new std::vector<std::vector<Card> >();
    for (int i = 0; i < playerCount; i++) {
        playerCards->push_back(std::vector<Card>());
        for (int j = 0; j < 5; j++) {
            playerCards->at(i).push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));

    std::map<playerName, int> otherPlayerCardCount;

    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.insert(std::pair<playerName, int>(playerName(i), playerCards->at(i).size()));
    }

    for (unsigned i = 0; i < players.size(); ++i) {

        players[playerName(i)]->gameInit(playerCards->at(i), cardDepot.back(), otherPlayerCardCount, currentPlayer);
    }
    players.at(currentPlayer)->doTurn(Card::NONE);
}

void GameController::playCard(playerName pName, const Card& card, Card::cardSuit whishedSuit)
{
    this->wishedSuit = whishedSuit;
    cardDepot.pushCard(card);
    foreach(Player * player, players)
    {
        if (player->getPName() != pName) {
            player->otherPlaysCard(pName, cardDepot.back());
        }
    }
    nextTurn();
}

void GameController::drawCard(playerName pName)
{
    players[pName]->reciveCard(cardStack.getLast(cardDepot));
    players[pName]->doTurn(wishedSuit);
    currentPlayerDrewCard = true;
    foreach(Player * player, players)
    {
        if (player->getPName() != pName) {
            player->otherDrawsCard(pName);
        }
    }
}

void GameController::doNothing(playerName pName)
{

    if (!currentPlayerDrewCard) {
        drawCard(pName);
    } else {
        nextTurn();
    }
}

Player* GameController::getBottomPlayer()
{
    return players.at(BOTTOM);
}

void GameController::nextTurn()
{
    setFlags(cardDepot.back());
    qDebug() << "Next Payer: " << currentPlayer;
    players[currentPlayer]->doTurn(wishedSuit);
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
        switch (currentPlayer) {
        case BOTTOM:
            currentPlayer = RIGHT;
            break;
        case LEFT:
            currentPlayer = BOTTOM;
            break;
        case TOP:
            currentPlayer = LEFT;
            break;
        case RIGHT:
            currentPlayer = RIGHT;
            break;
        }
    } else {
        switch (currentPlayer) {
        case BOTTOM:
            currentPlayer = LEFT;
            break;
        case LEFT:
            currentPlayer = TOP;
            break;
        case TOP:
            currentPlayer = RIGHT;
            break;
        case RIGHT:
            currentPlayer = BOTTOM;
            break;
        }
    }
}
