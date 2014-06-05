#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <settings.h>
#include <QTranslator>

OptionDialog::OptionDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);

    if (!Settings::getInstance()->getProperty("common/language").compare("")) {
        ui->languageCb->addItem("English");
        ui->languageCb->addItem("Deutsch");
    } else {

        ui->languageCb->addItem("Deutsch");
        ui->languageCb->addItem("English");
    }

    ui->portEdit->setText(Settings::getInstance()->getProperty("network/port"));
    ui->playernameEdit->setText(Settings::getInstance()->getProperty("common/playername"));

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(acceptButton()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(rejectButton()));
}

void OptionDialog::acceptButton()
{
    Settings::getInstance()->setProperty("network/port", ui->portEdit->text());
    Settings::getInstance()->setProperty("common/playername", ui->playernameEdit->text());

    QTranslator translator;

    if (ui->languageCb->currentText() == "English") {
        Settings::getInstance()->setProperty("common/language", "");
        QApplication::instance()->removeTranslator(&translator);
    } else {
        Settings::getInstance()->setProperty("common/language", "qtmaumau_de");
        QApplication::instance()->installTranslator(&translator);
    }
}

void OptionDialog::rejectButton()
{
    close();
}

OptionDialog::~OptionDialog()
{
    delete ui;
}
