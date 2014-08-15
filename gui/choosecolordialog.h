#ifndef CHOOSECOLORDIALOG_H
#define CHOOSECOLORDIALOG_H

#include <QtWidgets/QDialog>
#include <QMouseEvent>
#include <QtWidgets/QPushButton>
#include <QEvent>
#include <gameLogic/card.h>

namespace Ui {
class ChooseColorDialog;
}

class ChooseColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseColorDialog(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressed(QObject *pressedButton);
    ~ChooseColorDialog();

private:
    Ui::ChooseColorDialog *ui;
};

#endif // CHOOSECOLORDIALOG_H
