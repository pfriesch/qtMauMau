#include "gamecontroller.h"

void GameController::startGame(){
    cardStack = Deck(true);

    players.append(Player(Player::PlayerType::human,"Human"));
    players.append(Player(Player::PlayerType::ai,"Peter"));
    players.append(Player(Player::PlayerType::ai,"Manfred"));
    players.append(Player(Player::PlayerType::ai,"Maria"));
}


void GameController::playCard(Player &player, const Card &card)

{
    //TODO mb need to verify if this is a legal action
    player.dropCard(card);
    cardDepot.pushCard(card);
}

void GameController::drawCard(Player& player)
{
    Card card(cardStack.getLast(cardDepot));
    player.reciveCard(card);
}
