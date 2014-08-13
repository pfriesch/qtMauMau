#include "maumauprotokoll.h"
#include <QStringList>
#include <QDebug>

MProtocol::MProtocol()
{
}

QString MProtocol::cardVectorToSting(std::vector<Card> cards)
{
    //sting structure suit:value,suit:value,...
    QString vecSting;
    if (cards.size() == 0) {
        vecSting.append("$");
    } else {
        for (unsigned i = 0; i < cards.size(); ++i) {
            vecSting.append(cardToSting(cards.at(i)));
            vecSting.append(",");
        }
        //chop the last ","
        vecSting.chop(1);
    }
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

QString MProtocol::stringVecToSingle(std::vector<std::string> playerNames)
{
    QString singleString;
    for (int i = 0; i < playerNames.size(); ++i) {
        if (playerNames.at(i) != "") {
            singleString.append(QString(playerNames.at(i).c_str()));
        } else {
            singleString.append("$");
        }
        singleString.append(",");
    }
    //chop the last ","
    singleString.chop(1);
    return singleString;
}

std::vector<std::string> MProtocol::stringToStringVec(QString stringVec)
{
    std::vector<std::string> playerNames;
    QStringList strings = stringVec.split(",");
    for (int i = 0; i < strings.size(); ++i) {
        if (strings.at(i) == "$") {
            playerNames.push_back("");
        } else {
            playerNames.push_back(strings.at(i).toStdString());
        }
    }
    return playerNames;
}

std::vector<Card> MProtocol::stringToCardVec(QString vecAsSting)
{
    std::vector<Card> cards;
    if (!vecAsSting.contains("$")) {
        qDebug() << vecAsSting;
        QStringList vecAsStingList = vecAsSting.split(",");
        foreach(QString string, vecAsStingList)
        {
            cards.push_back(Card(MProtocol::stingToCard(string)));
        }
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
