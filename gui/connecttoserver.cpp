#include "connecttoserver.h"
#include "ui_connecttoserver.h"
#include <QMessageBox>

ConnectToServer::ConnectToServer(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ConnectToServer)
{
    ui->setupUi(this);

    //Set Port from Config
    QString port = Settings::getInstance()->getProperty("network/port");
    ui->porttxt->setText(port);
}

ConnectToServer::~ConnectToServer()
{
    delete ui;
}

void ConnectToServer::clientGameStarted()
{
    this->close();
}

void ConnectToServer::connectionRejected()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Connection rejected by Host!"));
    msgBox.exec();
    this->close();
}

void ConnectToServer::connectionAccepted()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Connection accepted by Host!"));
    msgBox.exec();
}

void ConnectToServer::on_connectbtn_clicked()
{
    emit connectToServer(ui->ipadresstxt->text(), ui->porttxt->text());
    ui->connectbtn->setDisabled(true);
    ui->connectbtn->setText("Waiting...");
}

void ConnectToServer::on_cancelbtn_clicked()
{
    this->close();
}
