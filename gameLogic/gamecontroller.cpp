#include "gamecontroller.h"


void QGameController::playCard(Player& player, const Card& card)
{
    //TODO mb need to verify if this is a legal action
    player.dropCard(card);
    cardDepot.pushCard(card);
}

void QGameController::drawCard(Player& player)
{
    Card card(cardStack.getLast(cardDepot));
    player.reciveCard(card);
}
