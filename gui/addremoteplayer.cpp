#include "addremoteplayer.h"
#include "ui_addremoteplayer.h"

AddRemotePlayer::AddRemotePlayer(QString address, QString name, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AddRemotePlayer)
{
    ui->setupUi(this);
    ui->playername->setText(name);
    ui->netaddress->setText(address);
}

AddRemotePlayer::~AddRemotePlayer()
{
    delete ui;
}
