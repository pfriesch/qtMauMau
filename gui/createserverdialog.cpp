#include "createserverdialog.h"
#include "ui_createserverdialog.h"

CreateServerDialog::CreateServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateServerDialog)
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

void CreateServerDialog::acceptButton()
{

}

void CreateServerDialog::rejectButton()
{
    close();
}
