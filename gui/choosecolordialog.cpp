#include "choosecolordialog.h"
#include "ui_choosecolordialog.h"

ChooseColorDialog::ChooseColorDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ChooseColorDialog)
{
    ui->setupUi(this);
    QPixmap pixmap("img/hearts.png");
    QIcon icon(pixmap);

    ui->btnFirst->setIcon(icon);
    ui->btnFirst->installEventFilter(this);

    ui->btnSecond->setIcon(QIcon(QPixmap("img/diamonds.png")));
    ui->btnSecond->installEventFilter(this);

    ui->btnThird->setIcon(QIcon(QPixmap("img/clubs.png")));
    ui->btnThird->installEventFilter(this);

    ui->btnFourth->setIcon(QIcon(QPixmap("img/spades.png")));
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
