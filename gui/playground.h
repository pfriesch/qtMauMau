#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QPointF>
#include <QHash>
#include <QString>
#include <vector>
#include <map>
#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include <QEventLoop>
#include <QDialog>
#include <gameLogic/gamecontroller.h>
#include <gameLogic/Card.h>
#include <gui/carditem.h>
#include <gui/playeritem.h>
#include <gui/animatedgraphicsscene.h>
#include <gui/choosecolordialog.h>
#include <gameLogic/PlayerName.h>
#include <settings.h>
#include <gui/soundmanager.h>
#include <QMessageBox>
#include <gui/gamehistory.h>
#include <QStringList>


class Playground : public AnimatedGraphicsScene {
    Q_OBJECT
public:
    explicit Playground(QObject* parent = 0);
    void startGame();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void rearrangeLayout();
    void setDepotNStack();

private:
    QVector<CardItem*> graphicalItems;
    QHash<PlayerItem::direction, PlayerItem*> players;

    CardItem depot;
    CardItem stack;
    int zValue = 1;
    Card::cardValue wishSuitCard;

    void updateDepotCard(CardItem& fromCard, CardItem& toCard, bool withAnimation = true);
    void updatePlayerCard(CardItem& fromCard, CardItem& toCard, bool withAnimation = true);
    void createPlayer(const std::vector<Card>& humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, std::vector<std::string> playerNames);
    Card::cardSuit chooseColor();

    GameHistory history;
    SoundManager soundMgr;

    //Layout entities
    int cardWidth = 71;
    int cardHeight = 96;
    int horizontalCardGap = 15;
    int verticalCardGap = 20;

public
slots:

    void initPlayground(const std::vector<Card>& humanPlayerCards,
                        std::map<PLAYER::Name, int> otherPlayerCardCount,
                        const Card& topDepotCard,
                        Card::cardValue _wishSuitCard,
                        std::vector<std::string> playerNames);
    //bekomme alle Karten und anzahl karten der anderen Mitspieler

    void playerDoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    // bekomme alle Spielbaren Karten von Human player

    void playerPlaysCard(PLAYER::Name player, const Card& playedCard);
    // Spieler spielt eine Karte und welche

    void playerDrawsCard(PLAYER::Name player);
    // Spieler zieht eine Karte

    void addPlayerCard(const Card& card);
    // Human Spieler hat eine Karte gezogen

    void playerWon(PLAYER::Name playerName);

signals:
    void playCard(const Card& card, Card::cardSuit whishedSuit);
    void drawCard();
};

#endif // PLAYGROUND_H
