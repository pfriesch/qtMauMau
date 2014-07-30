#include "connecttoserver.h"
#include "ui_connecttoserver.h"

ConnectToServer::ConnectToServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectToServer)
{
    ui->setupUi(this);

    //Set Port from Config
    QString port = Settings::getInstance()->getProperty("network/port");
    ui->porttxt->setText(port);

    //Set ClickListener on Btn
    connect(ui->connectbtn, SIGNAL(clicked()), this, SLOT(acceptButton()));
    connect(ui->cancelbtn, SIGNAL(clicked()), this, SLOT(rejectButton()));
}

ConnectToServer::~ConnectToServer()
{
    delete ui;
}

void ConnectToServer::acceptButton()
{

}

void ConnectToServer::rejectButton()
{
    close();
}
