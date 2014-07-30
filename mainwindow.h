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
    Playground *getPlayground() const;
    void resizeEvent (QResizeEvent *event);
    private
    slots:

private:
    void setupMenuBar();
    void setupGraphicsView();
    Playground *playground;
    OptionDialog* optionDialog;
    ConnectToServer* connectToServer;
    CreateServerDialog* createServerDialog;
};

#endif // MAINWINDOW_H
