#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QVector>
#include "gameLogic/card.h"
#include "gameLogic/playername.h"

/**
 * All communication with the maumau server goes through this client class.
 * Network communication is encoded through the mamau protokoll.
 * @brief The MauClient class handles the client side of a maumau game.
 */
class MauClient : public QObject {
    Q_OBJECT
public:
    MauClient(QObject* parent = 0);
    ~MauClient();
    //name of the player in the remote game controller
    PLAYER::Name playerName;
    QVector<PLAYER::Name> localPlayerOrder;
    void setupConnection(QString _address, QString _port);

signals:
    void UIinitPlayground(const std::vector<Card> humanPlayerCards, std::map<PLAYER::Name, int> otherPlayerCardCount, const Card& topDepotCard, Card::cardValue _wishSuitCard, std::vector<std::string> playerNames);
    void UIdoTurn(std::vector<Card> playableCards, Card::cardSuit wishedSuit);
    void UIplayerPlaysCard(PLAYER::Name pName, const Card& playedCard);
    void UIplayerDrawsCard(PLAYER::Name pName);
    void UIaddPlayerCard(const Card& card);
    void UIPlayerWon(std::string _title);
    void connectionRejected();
    void connectionAccepted();
    void clientGameStarted();

public
slots:
    void UIplaysCard(const Card& card, Card::cardSuit wishedSuit);
    void UIdrawsCard();

private
slots:
    void readNextData();
    void OnError();

private:
    QTcpSocket* server = new QTcpSocket();
    void writeNextData(QString data);
    void handleMessage(QString message);
    void rotatePlayerMap();
    PLAYER::Name getLocalPlayerPosition(PLAYER::Name remoteName);
    std::vector<std::string> getLocalPlayerNames(std::vector<std::string> playerNames);
};
#endif
