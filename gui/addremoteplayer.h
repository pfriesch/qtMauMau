#ifndef ADDREMOTEPLAYER_H
#define ADDREMOTEPLAYER_H

#include <QDialog>

namespace Ui {
class AddRemotePlayer;
}

class AddRemotePlayer : public QDialog {
    Q_OBJECT

public:
    explicit AddRemotePlayer(QString address, QString name, QWidget* parent = 0);
    ~AddRemotePlayer();

private:
    Ui::AddRemotePlayer* ui;
};

#endif // ADDREMOTEPLAYER_H
