#include "player.h"

std::vector<Card>& Player::getPlayableCards(const Card& card, Card::cardValue wishSuitCard)
{
 std::vector<Card>* playableCards = new std::vector<Card>;
  for (unsigned int i = 0; i < hand.size(); ++i) {
      if (card.getSuit() == hand[i].getSuit() || card.getValue() == hand[i].getValue() || card.getValue() == wishSuitCard) {
          playableCards->push_back(hand[i]);
      }
  }
  return *playableCards;
}
