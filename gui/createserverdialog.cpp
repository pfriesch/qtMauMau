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
        ui->player1txt->setText(adress);
        break;
    case 1:
        ui->player2txt->setText(adress);
        break;
    case 2:
        ui->player3txt->setText(adress);
        break;
    }
}

void CreateServerDialog::on_startgamebtn_clicked()
{
    emit startNetworkGame();
    close();
}

void CreateServerDialog::on_cancelbtn_clicked()
{
    close();
}
