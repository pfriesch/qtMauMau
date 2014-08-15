#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog {
    Q_OBJECT

public:
    explicit OptionDialog(QWidget* parent = 0);
    ~OptionDialog();

    private slots:
        void on_carddeck1_clicked();
        void on_carddeck2_clicked();
        void on_volumeSlider_valueChanged(int value);
        void on_buttonBox_2_accepted();
        void on_buttonBox_2_rejected();
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_okdiscardbtngrp_accepted();
        void on_okdiscardbtngrp_rejected();

private:
    void acceptEvent();
    Ui::OptionDialog* ui;
};

#endif // OPTIONDIALOG_H
