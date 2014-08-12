#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <settings.h>
#include <QTranslator>
#include "gameLogic/card.h"

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

    ui->carddeck1->setIcon(QIcon(QPixmap("img/deck_1/08.png")));
    ui->carddeck2->setIcon(QIcon(QPixmap("img/deck_2/08.gif")));

    if (Settings::getInstance()->getProperty("common/card_deck").toInt() == 1) {
        ui->carddeck1radio->setChecked(true);
    } else {
        ui->carddeck2radio->setChecked(true);
    }

    ui->portEdit->setText(Settings::getInstance()->getProperty("network/port"));
    ui->playernameEdit->setText(Settings::getInstance()->getProperty("common/playername"));
    ui->volumeSlider->setValue(Settings::getInstance()->getProperty("common/volume").toInt());
    ui->volumeIntLb->setText(Settings::getInstance()->getProperty("common/volume"));
}

void OptionDialog::acceptEvent()
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

    Settings::getInstance()->setProperty("common/volume", QString::number(ui->volumeSlider->value()));

    if (ui->carddeck1radio->isChecked()) {
        Settings::getInstance()->setProperty("common/card_deck", "1");
        Settings::getInstance()->setProperty("common/card_img_extension", ".png");
    } else {
        Settings::getInstance()->setProperty("common/card_deck", "2");
        Settings::getInstance()->setProperty("common/card_img_extension", ".gif");
    }

    Settings::getInstance()->setProperty("game/draw2xCard", QString::number(ui->draw2xcombo->currentIndex() + 1));
    Settings::getInstance()->setProperty("game/wishSuitCard", QString::number(ui->wishcombo->currentIndex() + 1));
    Settings::getInstance()->setProperty("game/skipNextCard", QString::number(ui->skipplayercombo->currentIndex() + 1));
    Settings::getInstance()->setProperty("game/changeDirectCard", QString::number(ui->changedirectcombo->currentIndex() + 1));
    close();
}

OptionDialog::~OptionDialog()
{
    delete ui;
}

void OptionDialog::on_carddeck1_clicked()
{
    ui->carddeck1radio->setChecked(true);
    ui->carddeck2radio->setChecked(false);
}

void OptionDialog::on_carddeck2_clicked()
{
    ui->carddeck1radio->setChecked(false);
    ui->carddeck2radio->setChecked(true);
}

void OptionDialog::on_volumeSlider_valueChanged(int value)
{
    ui->volumeIntLb->setText(QString::number(value, 10));
}

void OptionDialog::on_buttonBox_2_accepted()
{
    acceptEvent();
}

void OptionDialog::on_buttonBox_2_rejected()
{
    close();
}

void OptionDialog::on_buttonBox_accepted()
{
    acceptEvent();
}

void OptionDialog::on_buttonBox_rejected()
{
    close();
}

void OptionDialog::on_okdiscardbtngrp_accepted()
{
    acceptEvent();
}

void OptionDialog::on_okdiscardbtngrp_rejected()
{
    close();
}
