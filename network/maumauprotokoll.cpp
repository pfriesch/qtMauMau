#include "maumauprotokoll.h"
#include <QStringList>

MProtocol::MProtocol()
{
}

QString MProtocol::cardVectorToSting(std::vector<Card> cards)
{
    //sting structure suit:value,suit:value,...
    QString vecSting;
    for (unsigned i = 0; i < cards.size(); ++i) {
        vecSting.append(cardToSting(cards.at(i)));
        vecSting.append(",");
    }
    //chop the last ","
    vecSting.chop(1);
    return vecSting;
}

QString MProtocol::playerCardCountToSting(std::map<PLAYER::Name, int> otherPlayerCardCount)
{
    //sting structure: name:count,name:count,...
    QString cardCountString;
    for (unsigned i = 0; i < otherPlayerCardCount.size(); ++i) {
        cardCountString.append(QString::number(PLAYER::Name(i)));
        cardCountString.append(":");
        cardCountString.append(QString::number(otherPlayerCardCount.at(PLAYER::Name(i))));
        cardCountString.append(",");
    }
    //chop the last ","
    cardCountString.chop(1);
    return cardCountString;
}

QString MProtocol::cardToSting(Card card)
{
    //sting structure: suit:value
    QString cardAsString;
    cardAsString.append(QString::number(card.getSuit()));
    cardAsString.append(":");
    cardAsString.append(QString::number(card.getValue()));
    return cardAsString;
}

std::vector<Card> MProtocol::stringToCardVec(QString vecAsSting)
{
    std::vector<Card> cards;
    QStringList vecAsStingList = vecAsSting.split(",");
    foreach(QString string, vecAsStingList)
    {
        cards.push_back(Card(MProtocol::stingToCard(string)));
    }
    return cards;
}

std::map<PLAYER::Name, int> MProtocol::stingToCardCountMap(QString mapAsSting)
{
    std::map<PLAYER::Name, int> otherPlayerCardCount;
    QStringList pairs = mapAsSting.split(",");
    foreach(QString pair, pairs)
    {
        QStringList keyVal = pair.split(":");
        otherPlayerCardCount.insert(std::pair<PLAYER::Name, int>(PLAYER::Name(keyVal[0].toInt()), keyVal[1].toInt()));
    }
    return otherPlayerCardCount;
}

Card MProtocol::stingToCard(QString cardAsSting)
{
    QStringList cardAttrib = cardAsSting.split(":");

    Card card = Card(Card::cardSuit(cardAttrib[0].toInt()), Card::cardValue(cardAttrib[1].toInt()));
    return card;
}
