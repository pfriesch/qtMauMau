#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gui/playground.h>
#include "gui/optiondialog.h"
#include "gui/connecttoserver.h"
#include "gui/createserverdialog.h"
#include "gameLogic/humanplayer.h"
#include "network/server.h"
#include "network/client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent* event);
public
slots:
    void startNetworkGame(QVector<QPair<Player::Type, int> > players);
    void startGameAsClient();

private:
    void setupMenuBar();
    void setupGraphicsView();
    void connectSignalsForLocal(HumanPlayer* humanPlayer);
    void connectSignalsForServer(HumanPlayer* humanPlayer, QVector<RemotePlayer*> remotePlayers);
    void connectSignalsForClient();

    void showNameDialog();

    void resetGame();

    Playground* playground = NULL;
    GameController* gc = NULL;
    OptionDialog* optionDialog;
    ConnectToServer* connectToServer;
    CreateServerDialog* createServerDialog;
    MauServer* server;
    MauClient* client;

    //Game Starts
private
slots:
    void startGameAsLocal();
    void startGameAsServerDialog();
    void startGameAsClientDialog();
    void showOptionDialog();
};

#endif // MAINWINDOW_H
