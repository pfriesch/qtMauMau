#include "gamecontroller.h"
#include "gamecontrollerproxy.h"
#include "humanplayer.h"
#include "aiplayer.h"

#include <QDebug>

GameController::GameController(PLAYER::Name currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    //TODO what players do we have ?? remote??
    players.push_back(new HumanPlayer(PLAYER::Name::BOTTOM, GameControllerProxy(this, PLAYER::Name::BOTTOM)));
    for (int i = 1; i < playerCount; ++i) {
        players.push_back(new AIPlayer(PLAYER::Name(i), GameControllerProxy(this, PLAYER::Name(i))));
    }
}

void GameController::gameInit()
{
    cardStack.shuffle();
    std::vector<std::vector<Card> >* playerCards = new std::vector<std::vector<Card> >();
    for (int i = 0; i < playerCount; i++) {
        playerCards->push_back(std::vector<Card>());
        for (int j = 0; j < 5; j++) {
            playerCards->at(i).push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));

    std::map<PLAYER::Name, int> otherPlayerCardCount;
    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.insert(std::pair<PLAYER::Name, int>(PLAYER::Name(i), playerCards->at(i).size()));
    }
    for (unsigned i = 0; i < players.size(); ++i) {

        players[i]->gameInit(playerCards->at(i), cardDepot.back(), otherPlayerCardCount, currentPlayer);
    }
    players.at(static_cast<int>(currentPlayer))->doTurn(Card::NONE);
}

void GameController::playCard(PLAYER::Name pName, const Card& card, Card::cardSuit whishedSuit)
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

void GameController::drawCard(PLAYER::Name pName)
{
    if (!currentPlayerDrewCard) {
        players[static_cast<int>(pName)]->reciveCard(cardStack.getLast(cardDepot));
        currentPlayerDrewCard = true;
        foreach(Player * player, players)
        {
            if (player->getPName() != pName) {
                player->otherDrawsCard(pName);
            }
        }
    }
    players[pName]->doTurn(wishedSuit);
}

void GameController::doNothing(PLAYER::Name pName)
{

    if (!currentPlayerDrewCard) {
        drawCard(pName);
    } else {
        nextTurn();
    }
}

Player* GameController::getBottomPlayer()
{
    return players.at(PLAYER::BOTTOM);
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
        case PLAYER::BOTTOM:
            currentPlayer = PLAYER::RIGHT;
            break;
        case PLAYER::LEFT:
            currentPlayer = PLAYER::BOTTOM;
            break;
        case PLAYER::TOP:
            currentPlayer = PLAYER::LEFT;
            break;
        case PLAYER::RIGHT:
            currentPlayer = PLAYER::RIGHT;
            break;
        }
    } else {
        switch (currentPlayer) {
        case PLAYER::BOTTOM:
            currentPlayer = PLAYER::LEFT;
            break;
        case PLAYER::LEFT:
            currentPlayer = PLAYER::TOP;
            break;
        case PLAYER::TOP:
            currentPlayer = PLAYER::RIGHT;
            break;
        case PLAYER::RIGHT:
            currentPlayer = PLAYER::BOTTOM;
            break;
        }
    }
}
