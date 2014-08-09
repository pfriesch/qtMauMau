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
    switch (connectionIndex) {
    case 0:
        ui->player1statlbl->setEnabled(true);
        ui->player1statlbl->setText(adress);
        break;
    case 1:
        ui->player2statlbl->setEnabled(true);
        ui->player2statlbl->setText(adress);
        break;
    case 2:
        ui->player3statlbl->setEnabled(true);
        ui->player3statlbl->setText(adress);
        break;
    }
}

void CreateServerDialog::on_startgamebtn_clicked()
{
    //TODO add ai player in create server dialog
    if (aiPlayerCount != 0) {
        qDebug() << "aiplayer not handled in create server dialog";
    }
    emit startNetworkGame(aiPlayerCount);
    close();
}

void CreateServerDialog::on_cancelbtn_clicked()
{
    close();
}

void CreateServerDialog::on_addAiPlayer_clicked()
{

    if (aiPlayerCount != 0) {
        qDebug() << "try to add aiplayer, not handled in create server dialog";
    }
}
