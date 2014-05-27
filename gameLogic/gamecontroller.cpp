#include "gamecontroller.h"

GameController::GameController(int currentPlayer, int playerCount)
    : cardStack(Deck::FULL)
    , playerCount(playerCount)
    , currentPlayer(currentPlayer)
{
    if (playerCount < 2 || playerCount > 4) {
        throw std::invalid_argument("playercount has to be between 2 and 4");
    }
    players.push_back(HumanPlayer);
    for (int i = 0; i < playerCount; ++i) {
        players.push_back(AIPlayer);
    }
}

void GameController::playCard(const Card& card)
{
    players[humanPlayer].dropCard(card);
    cardDepot.pushCard(card);
    nextTurn();
}

void GameController::drawCard()
{
    if (!currentPlayerDrewCard) {
        Card drawnCard = cardStack.getLast(cardDepot);
        players[humanPlayer].reciveCard(drawnCard);
        currentPlayerDrewCard = true;
        emit addPlayerCard(drawnCard);
        emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
    } else {
        qDebug() << "Player tried to play card, though he's not allowed to.";
        emit playerDoTurn(players[currentPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
    }
}

void GameController::doNothing()
{
    if (!currentPlayerDrewCard) {
        drawCard();
        emit playerDoTurn(players[currentPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
    } else {
        nextTurn();
    }
}

//private
void GameController::gameInit()
{
    //TODO what players do we have ?? remote??
    cardStack.shuffle();
    //kind of players unregarded
    vector<vector<Card> > playerCards;
    for (int i = 0; i < playerCount; i++) {
        playerCards.push_back(vecotr<Card>);
        for (int j = 0; j < 5; j++) {
            playerCards[i].push_back(cardStack.getLast(cardDepot));
        }
    }
    cardDepot.pushCard(cardStack.getLast(cardDepot));
    vector<int> otherPlayerCardCount;
    for (unsigned int i = 0; i < players.size(); ++i) {
        otherPlayerCardCount.push_back(players[i].getCardCount());
    }
    int count = 0;
    foreach(Player player, players)
    {
        player.gameInit(playerCards[count], cardDepot.back(), otherPlayerCardCount);
        count++;
    }

    //    emit initPlayground(players[humanPlayer].getHand(), otherPlayerCardCount, cardDepot.back(), currentPlayer);
    //    emit playerDoTurn(players[humanPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
}
//private
void GameController::nextTurn()
{
    setFlags(cardDepot.back());
    qDebug() << "Next Payer: " << currentPlayer;
    switch (players[currentPlayer].getType()) {
    case Player::human:
        emit playerDoTurn(players[currentPlayer].getPlayableCards(cardDepot.back(), wishSuitCard));
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
    if (players[aiPlayer].getPlayableCards(cardDepot.back(), wishSuitCard).size() == 0) {
        players[aiPlayer].reciveCard(cardStack.getLast(cardDepot));
        emit playerDrawsCard(aiPlayer);
        if (players[aiPlayer].getPlayableCards(cardDepot.back(), wishSuitCard).size() == 0) {
            nextTurn();
        } else {
            //ai just plays the first playable card
            Card card = players[aiPlayer].getPlayableCards(cardDepot.back(), wishSuitCard)[0];
            players[aiPlayer].dropCard(card);
            cardDepot.pushCard(card);
            emit playerPlaysCard(aiPlayer, card);
            //TODO custom actions
            nextTurn();
        }
    } else {
        Card card = players[aiPlayer].getPlayableCards(cardDepot.back(), wishSuitCard)[0];
        players[aiPlayer].dropCard(card);
        cardDepot.pushCard(card);
        emit playerPlaysCard(aiPlayer, card);
        //TODO custom actions
        nextTurn();
    }
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
