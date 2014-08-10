#include "createserverdialog.h"
#include "ui_createserverdialog.h"
#include <QNetworkInterface>
#include "settings.h"

CreateServerDialog::CreateServerDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CreateServerDialog)
{
    ui->setupUi(this);
    foreach(const QHostAddress & address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            ui->currentIPadrBox->addItem(address.toString());
    }
    QString port = Settings::getInstance()->getProperty("network/port");
    ui->currentportlbl->setText(port);
}

CreateServerDialog::~CreateServerDialog()
{
    delete ui;
}

void CreateServerDialog::newPlayer(QString adress, int connectionIndex, QString name)
{
    if (getFreeSlots() <= 0) {
        QLabel* label = getNextFreeSlot();
        if (label != NULL) {
            label->setEnabled(true);
            label->setText(adress);
            players.append(QPair<Player::Type, int>(Player::REMOTE_PLAYER, connectionIndex));
        }
    }
}

void CreateServerDialog::on_startgamebtn_clicked()
{
    if (players.size() < 1) {
        qDebug() << "hanlde to few players";
    } else {
        emit startNetworkGame(players);
        close();
    }
}

void CreateServerDialog::on_cancelbtn_clicked()
{
    close();
}

void CreateServerDialog::on_addAiPlayer_clicked()
{
    if (getFreeSlots() <= 0) {
        QLabel* label = getNextFreeSlot();
        if (label != NULL) {
            label->setEnabled(true);
            label->setText("Computer");
            players.append(QPair<Player::Type, int>(Player::AI_PLAYER, 0));
        }
    }
}

int CreateServerDialog::getFreeSlots()
{
    int freeSlots = 0;
    if (ui->player1statlbl->isEnabled()) {
        freeSlots++;
    }
    if (ui->player2statlbl->isEnabled()) {
        freeSlots++;
    }
    if (ui->player3statlbl->isEnabled()) {
        freeSlots++;
    }
}

QLabel* CreateServerDialog::getNextFreeSlot()
{
    if (!ui->player1statlbl->isEnabled()) {
        return ui->player1statlbl;
    } else if (!ui->player2statlbl->isEnabled()) {
        return ui->player2statlbl;
    } else if (!ui->player3statlbl->isEnabled()) {
        return ui->player3statlbl;
    }
    return NULL;
}
