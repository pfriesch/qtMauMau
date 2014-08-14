#include "aiplayer.h"
#include <cstdlib>
#include <ctime>

AIPlayer::AIPlayer(PLAYER::Name pName, GameControllerProxy _gameController, std::string name)
    : Player(pName, _gameController, name)
{
    srand(time(NULL));
}

void AIPlayer::otherPlaysCard(PLAYER::Name pName, const Card& playedCard)
{
    UNUSED(pName);
    UNUSED(playedCard);
}

void AIPlayer::otherDrawsCard(PLAYER::Name pName)
{
    UNUSED(pName);
}

void AIPlayer::doTurn(Card topCard, Card::cardSuit wishedSuit)
{
    std::vector<Card> playableCards = getPlayableCards(topCard, wishedSuit);
    if (playableCards.size() > 0) {
        //TODO ai choose better card
        Card playCard = getPlayCard(playableCards);
        Card::cardSuit aiWhischedSuit;
        if (playCard.getValue() == wishSuitCard) {
            aiWhischedSuit = getWhishedCardSuit();
        } else {
            aiWhischedSuit = Card::NONE;
        }
        dropCard(playableCards.at(0));
        gameController.playCard(playCard, aiWhischedSuit);
        topCard = playCard;
    } else {

        gameController.drawCard();
    }
}

void AIPlayer::gameInit(const std::vector<Card> hand, const Card& topCard, std::map<PLAYER::Name, int> otherPlayerCardCount, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames)
{
    wishSuitCard = _wishSuitCard;
    this->hand = hand;
    UNUSED(topCard);
    UNUSED(otherPlayerCardCount);
    UNUSED(playerNames);
}

void AIPlayer::reciveCard(const Card& card)
{
    this->hand.push_back(card);
}

void AIPlayer::playerWon(std::string _title)
{
    UNUSED(_title);
}

Card AIPlayer::getPlayCard(std::vector<Card> playableCards)
{
    return playableCards.at(rand() % playableCards.size());
}

Card::cardSuit AIPlayer::getWhishedCardSuit()
{
    int suitsCount[4] = { 0 };
    for (unsigned i = 0; i < hand.size(); ++i) {
        if (hand[i].getValue() != wishSuitCard) {
            suitsCount[hand[i].getSuit()]++;
        }
    }
    int maxIndex = 0;
    int maxCount = 0;
    for (unsigned i = 0; i < 4; ++i) {
        if (suitsCount[i] > maxCount) {
            maxCount = suitsCount[i];
            maxIndex = i;
        }
    }
    return Card::cardSuit(maxIndex);
}
