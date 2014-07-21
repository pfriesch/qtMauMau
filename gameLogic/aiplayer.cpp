//#include "aiplayer.h"

//AIPlayer::AIPlayer(int playerId)
//    : Player(playerId)
//{
//}

//void AIPlayer::otherPlaysCard(int playerId, const Card& playedCard)
//{
//  topCard = playedCard;
//}

//void AIPlayer::otherDrawsCard(int playerId)
//{
//}

//void AIPlayer::doTurn(Card::cardSuit wishSuitCard)
//{
//    std::vector<Card> playableCards = getPlayableCards(topCard, wishSuitCard);
//    if (playableCards.size() > 0) {
//        emit playCard(playerId, playableCards.at(0));
//        drewCard = false;
//    } else if (!drewCard) {
//        emit drawCard(playerId);
//        drewCard = true;
//    } else {
//        emit doNothing(playerId);
//        drewCard = false;
//    }
//}

//void AIPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int playerId)
//{
//    this->hand = hand;
//    this->topCard = topCard;
//    this->playerId = playerId;
//}

//void AIPlayer::reciveCard(const Card& card)
//{
//    this->hand.push_back(card);
//}

//int AIPlayer::getCardCount() const
//{
//    return this->hand.size();
//}
