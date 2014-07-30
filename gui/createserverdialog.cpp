#include "createserverdialog.h"
#include "ui_createserverdialog.h"

CreateServerDialog::CreateServerDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CreateServerDialog)
{
    ui->setupUi(this);

    //Set ClickListener on Btn
    connect(ui->startgamebtn, SIGNAL(clicked()), this, SLOT(acceptButton()));
    connect(ui->cancelbtn, SIGNAL(clicked()), this, SLOT(rejectButton()));
}

CreateServerDialog::~CreateServerDialog()
{
    delete ui;
}

void CreateServerDialog::newPlayer(QString adress, int connectionIndex, QString name)
{
    switch (connectionIndex) {
    case 1:
        ui->player1txt->setText(adress);
        break;
    case 2:
        ui->player2txt->setText(adress);
        break;
    case 3:
        ui->player3txt->setText(adress);
        break;
    }
}

void CreateServerDialog::acceptButton()
{
}

void CreateServerDialog::rejectButton()
{
    close();
}
