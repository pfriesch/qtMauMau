#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog {
    Q_OBJECT

public:
    explicit OptionDialog(QWidget* parent = 0);
    ~OptionDialog();

    private slots:
        void acceptButton();
        void rejectButton();

private:
    Ui::OptionDialog* ui;
};

#endif // OPTIONDIALOG_H
