#include "gamecontroller.h"

GameController::GameController(int currentPlayer, int playerCount)
    : cardStack(true)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    players.push_back(Player(Player::human, "Hans"));
    for (int i = 0; i < playerCount; ++i) {
        players.push_back(Player(Player::ai));
    }
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
        emit addPlayerCard(drawnCard);
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
    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    dealCards();
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    vector<int> otherPlayerCardCount;
    for (int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.push_back(players[i].getCardCount());
    }
    emit initPlayground(players[humanPlayer].getHand(), otherPlayerCardCount, cardDepot.back(), currentPlayer);
    emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back()));
}
//private
void GameController::dealCards()
{
    for (int i = 0; i < playerCount; i++) {
        for (int j = 0; j < 5; j++) {
            players[i].reciveCard(cardStack.getLast(cardDepot));
        }
    }
}
//private
void GameController::nextTurn()
{
    if (currentPlayer < playerCount-1) {
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
        //TODO add remote player action
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
