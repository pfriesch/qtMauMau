#include "gamecontroller.h"
#include "gamecontrollerproxy.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include "remoteplayer.h"

#include <QDebug>
#include "algorithm"

GameController::GameController()
    : cardStack(Deck::FULL)
{
}
void GameController::localGame(int playerCount)
{
    if (playerCount < MIN_PLAYER || playerCount > MAX_PLAYER) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    } else {
        players.push_back(new HumanPlayer(PLAYER::Name::BOTTOM, GameControllerProxy(this, PLAYER::Name::BOTTOM)));
        playerOrder.push_back(PLAYER::BOTTOM);
        for (int i = 1; i < playerCount; ++i) {
            players.push_back(new AIPlayer(PLAYER::Name(i), GameControllerProxy(this, PLAYER::Name(i))));
            playerOrder.push_back(PLAYER::Name(i));
        }
    }
}

void GameController::networkGame(std::vector<Player*> _players)
{
    players.push_back(new HumanPlayer(PLAYER::Name::BOTTOM, GameControllerProxy(this, PLAYER::Name::BOTTOM)));
    playerOrder.push_back(PLAYER::BOTTOM);
    for (unsigned i = 0; i < _players.size(); ++i) {
        players.push_back(_players.at(i));
        playerOrder.push_back(PLAYER::Name(i + 1));
    }
}

void GameController::gameInit(Card::cardValue _draw2xCard,
                              Card::cardValue _wishSuitCard,
                              Card::cardValue _skipNextCard,
                              Card::cardValue _changeDirectCard)
{
    Card::cardValue draw2xCard = _draw2xCard;
    Card::cardValue wishSuitCard = _wishSuitCard;
    Card::cardValue skipNextCard = _skipNextCard;
    Card::cardValue changeDirectCard = _changeDirectCard;
    cardStack.shuffle();
    std::vector<std::vector<Card> >* playerCards = new std::vector<std::vector<Card> >();
    for (unsigned i = 0; i < players.size(); i++) {
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

        players[i]->gameInit(playerCards->at(i), cardDepot.back(), otherPlayerCardCount, playerOrder[0]);
    }
    players[playerOrder[0]]->doTurn(Card::NONE);
}

void GameController::playCard(PLAYER::Name pName, const Card& card, Card::cardSuit whishedSuit)
{
    if (playerOrder[0] == pName && !playerPlayed) {
        playerPlayed = true;
        this->wishedSuit = whishedSuit;
        cardDepot.pushCard(card);
        foreach(Player * player, players)
        {
            if (player->getPName() != pName) {
                player->otherPlaysCard(pName, cardDepot.back());
            }
        }
        setFlags(card);
        if (!players[playerOrder[0]]->getCardCount()) {
            playerWon(playerOrder[0]);
        }
        if (skipNextPlayer) {
            setNextPlayer();
            skipNextPlayer = false;
        }
        nextTurn();
    }
}

void GameController::drawCard(PLAYER::Name pName)
{
    if (playerOrder[0] == pName && !playerPlayed) {
        playerPlayed = true;
        playerDrawCard(pName);
        handleDraw2x();
        nextTurn();
    }
}

void GameController::setdraw2xCard(Card::cardValue cardValue)
{
    draw2xCard = cardValue;
}

Card::cardValue GameController::getWhishSuitCard()
{
    return wishSuitCard;
}

Player* GameController::getBottomPlayer()
{
    return players.at(PLAYER::BOTTOM);
}

void GameController::nextTurn()
{
    if (!aPlayerWon) {
        playerPlayed = false;
        setNextPlayer();
        qDebug() << "Next Payer: " << playerOrder[0];
        players[playerOrder[0]]->doTurn(wishedSuit);
    } else {
        qDebug() << "some player won !!!!!";
    }
}

void GameController::setFlags(const Card& card)
{
    if (card.getValue() == changeDirectCard) {
        if (changedDirection) {
            changedDirection = false;
        } else {
            changedDirection = true;
        }
    }
    if (card.getValue() == wishSuitCard) {
        //already handled by play card
    }
    if (card.getValue() == draw2xCard) {
        if (draw2x) {
            draw2xCount = draw2xCount + 2;
        } else {
            draw2x = true;
            draw2xCount = 2;
        }
    } else {
        handleDraw2x();
    }
    if (card.getValue() == skipNextCard) {
        skipNextPlayer = true;
    }
}

void GameController::handleDraw2x()
{
    if (draw2x) {
        for (int i = 0; i < draw2xCount; ++i) {
            playerDrawCard(playerOrder[0]);
        }
        draw2xCount = 0;
        draw2x = false;
    }
}

void GameController::playerWon(PLAYER::Name playerName)
{
    for (unsigned i = 0; i < players.size(); ++i) {
        players[i]->playerWon(playerName);
    }
    aPlayerWon = true;
}

void GameController::setNextPlayer()
{
    if (changedDirection) {
        std::rotate(playerOrder.begin(), playerOrder.begin() + 1, playerOrder.end());
    } else {
        std::rotate(playerOrder.begin(), playerOrder.end() - 1, playerOrder.end());
    }
}

void GameController::playerDrawCard(PLAYER::Name pName)
{
    players[pName]->reciveCard(cardStack.getLast(cardDepot));
    foreach(Player * player, players)
    {
        if (player->getPName() != pName) {
            player->otherDrawsCard(pName);
        }
    }
}
