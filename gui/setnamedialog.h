#ifndef SETNAMEDIALOG_H
#define SETNAMEDIALOG_H

#include <QtWidgets/QDialog>
#include <settings.h>

namespace Ui {
class SetNameDialog;
}

class SetNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetNameDialog(QWidget *parent = 0);
    ~SetNameDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::SetNameDialog *ui;
};

#endif // SETNAMEDIALOG_H
