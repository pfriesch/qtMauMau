#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include <QFile>
#include <QString>
#include <QIODevice>
#include <gui/carditem.h>
#include <QTextStream>

class GameHistory
{
public:
    GameHistory();
    void write(QString text,QVector<CardItem*>* cards);
    void write(QString text);
    QString filename = "gamehistory.txt";
    QFile *file;
    void write(QString text, CardItem &card);
    void write(QString text, Card::cardSuit suit, Card::cardValue value);
    ~GameHistory();
private:
    QString cardToString(CardItem item);
};

#endif // GAMEHISTORY_H
