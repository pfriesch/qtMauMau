#ifndef CREATESERVERDIALOG_H
#define CREATESERVERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPair>
#include <gameLogic/remoteplayer.h>
#include <gameLogic/aiplayer.h>

namespace Ui {
class CreateServerDialog;
}

class CreateServerDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreateServerDialog(QWidget* parent = 0);
    ~CreateServerDialog();
signals:
    void startNetworkGame(QVector<QPair<Player::Type, int> > players);

public
slots:
    void newPlayer(QString adress, int connectionIndex, QString name);

private
slots:
    void on_startgamebtn_clicked();

    void on_cancelbtn_clicked();

    void on_addAiPlayer_clicked();

private:
    Ui::CreateServerDialog* ui;
    QVector<QPair<Player::Type, int> > players;
    int getFreeSlots();
    QLabel* getNextFreeSlot();
};

#endif // CREATESERVERDIALOG_H
