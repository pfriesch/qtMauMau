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
  void startNetworkGame();

public
slots:
    void newPlayer(QString adress, int connectionIndex, QString name);

private
slots:
    void on_startgamebtn_clicked();

    void on_cancelbtn_clicked();

private:
    Ui::CreateServerDialog* ui;
};

#endif // CREATESERVERDIALOG_H
