#ifndef CARD_H_
#define CARD_H_

class Card {
public:
    enum cardSuit {
        HEARTS = 0,
        DIAMONDS = 1,
        CLUBS = 2,
        SPADES = 3,
    };
    enum cardValue {
        SEVEN = 1,
        EIGHT = 2,
        NINE = 3,
        TEN = 4,
        JACK = 5,
        QUEEN = 6,
        KING = 7,
        ACE = 8,
    };

private:
    Card::cardSuit suit;
    Card::cardValue value;

public:
    Card(cardSuit cSuit, cardValue cValue);
    Card(const Card& card);
    Card();
    cardSuit getSuit() const;
    cardValue getValue() const;
    bool operator==(const Card& card) const;
};

#endif /* CARD_H_ */
