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
}

void GameController::drawCard()
{
    players[humanPlayer].reciveCard(cardStack.getLast(cardDepot));
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
