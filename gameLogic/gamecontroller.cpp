#include "gamecontroller.h"
#include "gamecontrollerproxy.h"
#include <QDebug>

GameController::GameController(Player::playerName currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    //    players.push_back(new HumanPlayer(0));
    //    for (int i = 1; i < playerCount; ++i) {
    //        players.push_back(new AIPlayer(i));
    //    }
}

void GameController::gameInit()
{

    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    std::vector<std::vector<Card> >* playerCards = new std::vector<std::vector<Card> >;
    for (int i = 0; i < playerCount; i++) {
        playerCards->push_back(std::vector<Card>());
        for (int j = 0; j < 5; j++) {
            playerCards->at(i).push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    std::vector<int>* otherPlayerCardCount = new std::vector<int>;
    for (unsigned int i = 1; i < players.size(); ++i) {
        otherPlayerCardCount->push_back(playerCards->at(i).size());
    }
    for (unsigned i = 0; i < players.size(); ++i) {

        players[Player::playerName(i)]->gameInit(playerCards->at(i), cardDepot.back(), *otherPlayerCardCount, currentPlayer);
    }
    players.at(currentPlayer)->doTurn(Card::NONE, GameControllerProxy(this, currentPlayer));
}

//HumanPlayer* GameController::getHumanPlayer()
//{
//    HumanPlayer* player = qobject_cast<HumanPlayer*>(players[0]);
//    qDebug() << "";
//    return player;
//}

void GameController::playCard(Player::playerName pName, const Card& card, Card::cardSuit whishedSuit)
{
    if (currentPlayer == pName) {
        cardDepot.pushCard(card);
        nextTurn();
    }
}

void GameController::drawCard(Player::playerName pName)
{
    if (currentPlayer == pName) {
        if (!currentPlayerDrewCard) {
            players[pName]->reciveCard(cardStack.getLast(cardDepot));
            players[pName]->doTurn(wishedSuit, GameControllerProxy(this, currentPlayer));
            currentPlayerDrewCard = true;
            foreach(Player * player, players)
            {
                if (player->getPName() != pName) {
                    player->otherDrawsCard(pName);
                }
            }
        }
    }
}

void GameController::doNothing(Player::playerName pName)
{
    if (currentPlayer == pName) {
        if (!currentPlayerDrewCard) {
            players[pName]->reciveCard(cardStack.getLast(cardDepot));
            players[pName]->doTurn(wishedSuit,GameControllerProxy(this, currentPlayer));
            currentPlayerDrewCard = true;
        } else {
            nextTurn();
        }
    }
}

void GameController::nextTurn()
{
    setFlags(cardDepot.back());
    qDebug() << "Next Payer: " << currentPlayer;
    players[currentPlayer]->doTurn(wishedSuit, GameControllerProxy(this, currentPlayer));
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
        case Player::BOTTOM:
            currentPlayer = Player::RIGHT;
            break;
        case Player::LEFT:
            currentPlayer = Player::BOTTOM;
            break;
        case Player::TOP:
            currentPlayer = Player::LEFT;
            break;
        case Player::RIGHT:
            currentPlayer = Player::RIGHT;
            break;
        }
    } else {
        switch (currentPlayer) {
        case Player::BOTTOM:
            currentPlayer = Player::LEFT;
            break;
        case Player::LEFT:
            currentPlayer = Player::TOP;
            break;
        case Player::TOP:
            currentPlayer = Player::RIGHT;
            break;
        case Player::RIGHT:
            currentPlayer = Player::BOTTOM;
            break;
        }
    }
}
