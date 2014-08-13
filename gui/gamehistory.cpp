#include "gamehistory.h"


GameHistory::GameHistory()
{
    file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Append);
    if (file->size() > 5000) {
        file->remove();
        delete file;
        file = new QFile(filename);
        file->open(QIODevice::WriteOnly | QIODevice::Append);
    }
}

void GameHistory::write(QString text)
{
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << text << "\n";
}

void GameHistory::write(QString text, QVector<CardItem*>* cards)
{
    QString hand;
    for (int i = 0; i < cards->size(); ++i) {
        hand += cardToString(*(cards->at(i)));
        hand += " ";
    }
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

void GameHistory::write(QString text, CardItem &card)
{
    QString hand;
    hand += cardToString(card);
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

void GameHistory::write(QString text, Card::cardSuit suit, Card::cardValue value)
{
    QString hand;
    Card c = Card(suit,value);
    CardItem item = CardItem(c);
    hand += cardToString(item);
    QString full(text + " - "+ hand);
    QTextStream out(file);
    out.setAutoDetectUnicode(true);
    out << full << "\n";
}

QString GameHistory::cardToString(CardItem item){
        QString hand;
        switch (item.getCard().getValue()) {
        case Card::cardValue::SEVEN: hand += "7 "; break;
        case Card::cardValue::EIGHT: hand += "8 "; break;
        case Card::cardValue::NINE: hand += "9 "; break;
        case Card::cardValue::TEN: hand += "10 "; break;
        case Card::cardValue::JACK: hand += "Jack "; break;
        case Card::cardValue::QUEEN: hand += "Queen "; break;
        case Card::cardValue::KING: hand += "King "; break;
        case Card::cardValue::ACE: hand += "Ace "; break;
        }

        switch (item.getCard().getSuit()) {
        case Card::cardSuit::HEARTS: hand += "Hearts"; break;
        case Card::cardSuit::SPADES: hand += "Spades"; break;
        case Card::cardSuit::DIAMONDS: hand += "Diamonds"; break;
        case Card::cardSuit::CLUBS: hand += "Clubs"; break;
        }
        return hand;
}
GameHistory::~GameHistory(){
    delete file;
}
