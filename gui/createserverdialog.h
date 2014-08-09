#ifndef CREATESERVERDIALOG_H
#define CREATESERVERDIALOG_H

#include <QDialog>

namespace Ui {
class CreateServerDialog;
}

class CreateServerDialog : public QDialog {
    Q_OBJECT

public:
    explicit CreateServerDialog(QWidget* parent = 0);
    ~CreateServerDialog();
signals:
    void startNetworkGame(int aiPlayerCount);

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
    int aiPlayerCount = 0;
};

#endif // CREATESERVERDIALOG_H
