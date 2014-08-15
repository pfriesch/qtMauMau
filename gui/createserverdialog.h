#ifndef CREATESERVERDIALOG_H
#define CREATESERVERDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <gameLogic/remoteplayer.h>
#include <gameLogic/aiplayer.h>
#include "gameLogic/playername.h"
#include <QVector>
#include <QStringList>

namespace Ui {
class CreateServerDialog;
}

class CreateServerDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreateServerDialog(QWidget* parent = 0);
    ~CreateServerDialog();
signals:
    void startNetworkGame(QVector<Player::Type> players, QStringList playerNames);
    void playerRejected(int pendingConIndex);
    void playerAccepted(int pendingConIndex);

public
slots:
    void newPlayer(QString address, int connectionIndex, QString name);

private
slots:
    void on_startgamebtn_clicked();

    void on_cancelbtn_clicked();

    void on_addAiPlayer_clicked();

private:
    Ui::CreateServerDialog* ui;
    QVector<Player::Type> players;
    int getFreeSlotsCount();
    QVector<QLabel*> getNextFreeSlot();
    bool acceptRemotePlayer(QString address, QString name);
    QStringList getPlayerNames();
};

#endif // CREATESERVERDIALOG_H
