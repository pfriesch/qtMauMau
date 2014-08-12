#include "choosecolordialog.h"
#include "ui_choosecolordialog.h"

ChooseColorDialog::ChooseColorDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ChooseColorDialog)
{
    ui->setupUi(this);
    QPixmap pixmap("img/hearts.png");
    QIcon icon(pixmap);

    ui->btnHearts->setIcon(icon);
    ui->btnHearts->installEventFilter(this);

    ui->btnDiamonds->setIcon(QIcon(QPixmap("img/diamonds.png")));
    ui->btnDiamonds->installEventFilter(this);

    ui->btnClubs->setIcon(QIcon(QPixmap("img/clubs.png")));
    ui->btnClubs->installEventFilter(this);

    ui->btnSpades->setIcon(QIcon(QPixmap("img/spades.png")));
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
