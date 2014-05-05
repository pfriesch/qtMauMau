#include "gamecontroller.h"

//void QGameController::playCard(Player& player, const Card& card)
//{
//    //TODO mb need to verify if this is a legal action
//    player.dropCard(card);
//    cardDepot.pushCard(card);
//}

//void QGameController::drawCard(Player& player)
//{
//    Card card(cardStack.getLast(cardDepot));
//    player.reciveCard(card);
//}

GameController::GameController(int currentPlayer)
    : currentPlayer(currentPlayer)
    , cardStack(true)
{
    //TODO what players do we have ?? remote??
    gameInit();
    int* otherPlayerCardCount = new int[4];
    for (int i = 0; i < players.length(); ++i) {
        otherPlayerCardCount[i] = players[i].getCardCount();
    }
    emit initPlayground(players[humanPlayer].getHand(), otherPlayerCardCount, cardDepot.back(), currentPlayer);
}

void GameController::playCard(const Card& card)
{
    //TODO check if valid
    players[humanPlayer].dropCard(card);
    cardDepot.pushCard(card);
    //TODO custom actions
    nextTurn();
}

void GameController::drawCard()
{
    if (!currentPlayerDrewCard) {
        Card drawnCard = cardStack.getLast(cardDepot);
        players[humanPlayer].reciveCard(drawnCard);
        currentPlayerDrewCard = true;
        emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back()));
    } else {
        //TODO error handling
    }
}

void GameController::doNothing()
{
    if (!currentPlayerDrewCard) {
        drawCard();
    } else {
        //TODO continue game
    }
}

//private
void GameController::gameInit()
{
    cardStack.shuffle();
    //kind of players unregarded
    players.push_back(Player(Player::human, "Hans"));
    players.push_back(Player(Player::ai));
    players.push_back(Player(Player::ai));
    players.push_back(Player(Player::ai));
    dealCards();
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back()));
}
//private
void GameController::dealCards()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            players[i].reciveCard(cardStack.getLast(cardDepot));
        }
    }
}
//private
void GameController::nextTurn()
{
    if (currentPlayer < 4) {
        currentPlayer++;
    } else {
        currentPlayer = 0;
    }
    switch (players[currentPlayer].getType()) {
    case Player::human:
        emit playerDoTurn(players[currentPlayer].getPlayableCards(cardDepot.back()));
        break;
    case Player::ai:
        aiDoTurn(currentPlayer);
        break;
    case Player::remote:
        //TODO
        break;
    default:
        break;
    }
}

void GameController::aiDoTurn(int aiPlayer)
{
    if (players[aiPlayer].getPlayableCards(cardDepot.back()).size() == 0) {
        players[aiPlayer].reciveCard(cardStack.getLast(cardDepot));
        emit playerDrawsCard(aiPlayer);
        if (players[aiPlayer].getPlayableCards(cardDepot.back()).size() == 0) {
            nextTurn();
        } else {
            //ai just plays the first playable card
            Card card = players[aiPlayer].getPlayableCards(cardDepot.back())[0];
            players[aiPlayer].dropCard(card);
            cardDepot.pushCard(card);
            emit playerPlaysCard(aiPlayer, card);
            //TODO custom actions
            nextTurn();
        }
    } else {
        Card card = players[aiPlayer].getPlayableCards(cardDepot.back())[0];
        players[aiPlayer].dropCard(card);
        cardDepot.pushCard(card);
        emit playerPlaysCard(aiPlayer, card);
        //TODO custom actions
        nextTurn();
    }
}
