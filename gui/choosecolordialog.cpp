#include "choosecolordialog.h"
#include "ui_choosecolordialog.h"
#include "settings.h"

ChooseColorDialog::ChooseColorDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ChooseColorDialog)
{
    ui->setupUi(this);

    QString deckNumber = Settings::getInstance()->getProperty("common/card_deck");
    QString imgExtension = Settings::getInstance()->getProperty("common/card_img_extension");


    ui->btnFirst->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/hearts" + imgExtension)));
    ui->btnFirst->installEventFilter(this);

    ui->btnSecond->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/diamonds" + imgExtension)));
    ui->btnSecond->installEventFilter(this);

    ui->btnThird->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/clubs" + imgExtension)));
    ui->btnThird->installEventFilter(this);

    ui->btnFourth->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/spades" + imgExtension)));
    ui->btnFourth->installEventFilter(this);
}

bool ChooseColorDialog::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        mousePressed(obj);
        break;
    default:
        break;
    }
    // pass the event on to the parent class
    return QDialog::eventFilter(obj, event);
}

void ChooseColorDialog::mousePressed(QObject* pressedButton)
{

    int cardSuit = 0;

    if (pressedButton == ui->btnFirst) {
        cardSuit = Card::cardSuit(0);
    } else if (pressedButton == ui->btnSecond) {
        cardSuit = Card::cardSuit(1);
    } else if (pressedButton == ui->btnThird) {
        cardSuit = Card::cardSuit(2);
    } else if (pressedButton == ui->btnFourth) {
        cardSuit = Card::cardSuit(3);
    }
    this->done(cardSuit);
}

ChooseColorDialog::~ChooseColorDialog()
{
    delete ui;
}
