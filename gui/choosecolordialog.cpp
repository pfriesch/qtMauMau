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

    ui->btnHearts->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/hearts" + imgExtension)));
    ui->btnHearts->installEventFilter(this);

    ui->btnDiamonds->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/diamonds" + imgExtension)));
    ui->btnDiamonds->installEventFilter(this);

    ui->btnClubs->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/clubs" + imgExtension)));
    ui->btnClubs->installEventFilter(this);

    ui->btnSpades->setIcon(QIcon(QPixmap("img/deck_" + deckNumber + "/spades" + imgExtension)));
    ui->btnSpades->installEventFilter(this);
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

    if (pressedButton == ui->btnHearts) {
        cardSuit = Card::HEARTS;
    } else if (pressedButton == ui->btnDiamonds) {
        cardSuit = Card::DIAMONDS;
    } else if (pressedButton == ui->btnClubs) {
        cardSuit = Card::CLUBS;
    } else if (pressedButton == ui->btnSpades) {
        cardSuit = Card::SPADES;
    }
    this->done(cardSuit);
}

ChooseColorDialog::~ChooseColorDialog()
{
    delete ui;
}
