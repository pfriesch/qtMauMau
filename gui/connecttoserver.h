#ifndef CONNECTTOSERVER_H
#define CONNECTTOSERVER_H

#include <QDialog>
#include <settings.h>

namespace Ui {
class ConnectToServer;
}

class ConnectToServer : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectToServer(QWidget *parent = 0);
    ~ConnectToServer();

private slots:
    void acceptButton();
    void rejectButton();

private:
    Ui::ConnectToServer *ui;
};

#endif // CONNECTTOSERVER_H
