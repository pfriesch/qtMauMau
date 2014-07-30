#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gui/playground.h>
#include "gui/optiondialog.h"
#include "gui/connecttoserver.h"
#include "gui/createserverdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    void resizeEvent (QResizeEvent *event);

private:
    void setupMenuBar();
    void setupGraphicsView();
    void connectSignalsForLocal();
    void connectSignalsForServer();
    void setupGameController();

    void resetGame();

    GameController *gc = NULL;
    Playground *playground = NULL;
    OptionDialog* optionDialog;
    ConnectToServer* connectToServer;
    CreateServerDialog* createServerDialog;

    //Game Starts
private slots:
    void startGameAsLocal();
    void startGameAsServer();
    void startGameAsClient();
};

#endif // MAINWINDOW_H
