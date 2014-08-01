#include "setnamedialog.h"
#include "ui_setnamedialog.h"

SetNameDialog::SetNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetNameDialog)
{
    ui->setupUi(this);
    ui->playernametxt->setText(Settings::getInstance()->getProperty("common/playername"));
}

SetNameDialog::~SetNameDialog()
{
    delete ui;
}
void SetNameDialog::on_buttonBox_accepted(){
    QString playername = ui->playernametxt->text();
    if(Settings::getInstance()->getProperty("common/playername").compare(playername) != 0){
        Settings::getInstance()->setProperty("common/playername",playername);
        Settings::getInstance()->setProperty("common/changed_playername","1");
    }
}

void SetNameDialog::on_buttonBox_rejected()
{
    close();
}
