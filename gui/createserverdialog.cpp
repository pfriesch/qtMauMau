#include "createserverdialog.h"
#include "ui_createserverdialog.h"
#include <QNetworkInterface>
#include "settings.h"
#include "gui/addremoteplayer.h"

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

void CreateServerDialog::newPlayer(QString address, int connectionIndex, QString name)
{
    if (getFreeSlotsCount() >= 0) {
        if (acceptRemotePlayer(address, name)) {
            emit playerAccepted(connectionIndex);
            QVector<QLabel*> labelPair = getNextFreeSlot();
            labelPair.at(0)->setEnabled(true);
            labelPair.at(1)->setEnabled(true);
            labelPair.at(0)->setText(name);
            labelPair.at(1)->setText(address);
            players.append(Player::REMOTE_PLAYER);

        } else {
            emit playerRejected(connectionIndex);
        }
    } else {
        emit playerRejected(connectionIndex);
    }
}

void CreateServerDialog::on_startgamebtn_clicked()
{
    if (players.size() < 1) {
        qDebug() << "too few players";
    } else {
        emit startNetworkGame(players, getPlayerNames());
        close();
    }
}

void CreateServerDialog::on_cancelbtn_clicked()
{
    close();
}

void CreateServerDialog::on_addAiPlayer_clicked()
{
    if (getFreeSlotsCount() >= 0) {
        QVector<QLabel*> labelPair = getNextFreeSlot();
        labelPair.at(0)->setEnabled(true);
        labelPair.at(1)->setEnabled(true);
        labelPair.at(0)->setText("Computer");
        labelPair.at(1)->setText("-");
        players.append(Player::AI_PLAYER);
    }
}

int CreateServerDialog::getFreeSlotsCount()
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
    return freeSlots;
}

QVector<QLabel*> CreateServerDialog::getNextFreeSlot()
{
    QVector<QLabel*> lablePair;
    if (!ui->player1statlbl->isEnabled()) {
        lablePair.append(ui->player1namelbl);
        lablePair.append(ui->player1statlbl);
        return lablePair;
    } else if (!ui->player2statlbl->isEnabled()) {
        lablePair.append(ui->player2namelbl);
        lablePair.append(ui->player2statlbl);
        return lablePair;
    } else if (!ui->player3statlbl->isEnabled()) {
        lablePair.append(ui->player3namelbl);
        lablePair.append(ui->player3statlbl);
        return lablePair;
    }
    return QVector<QLabel*>();
}

bool CreateServerDialog::acceptRemotePlayer(QString address, QString name)
{

    AddRemotePlayer dialog(address, name, this);
    return dialog.exec();
}

QStringList CreateServerDialog::getPlayerNames()
{
    QStringList playerNames;
    for (int i = 0; i < players.size(); ++i) {
        switch (i) {
        case 0:
            playerNames.append(ui->player1namelbl->text());
            break;
        case 1:
            playerNames.append(ui->player2namelbl->text());
            break;
        case 2:
            playerNames.append(ui->player3namelbl->text());
            break;
        }
    }
    return playerNames;
}
