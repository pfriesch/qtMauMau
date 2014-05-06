#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gui/playground.h>
#include "gui/optiondialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    Playground *getPlayground() const;

    private
    slots:

private:
    void setupMenuBar();
    void setupGraphicsView();
    Playground *playground;
    OptionDialog* optionDialog;
};

#endif // MAINWINDOW_H
