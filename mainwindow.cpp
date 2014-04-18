#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QAction>
MainWindow::MainWindow(QWidget *parent)
{
    setupMenuBar();
}

/**
 * Sets up the Menubar for the MainWindow
 * @brief MainWindow::setupMenuBar
 */
void MainWindow::setupMenuBar(){
    QMenuBar *menuBar = new QMenuBar();

    // File Menu
    QMenu *fileMenu = new QMenu(QMenu::tr("File"));
    menuBar->addMenu(fileMenu);

    QAction *startGameMenu = new QAction(QAction::tr("Start Game"),this);
    fileMenu->addAction(startGameMenu);

    QAction *optionsMenu = new QAction(QAction::tr("Options"),this);
    fileMenu->addAction(optionsMenu);

    QAction *exitMenu = new QAction(QAction::tr("Exit"),this);
    fileMenu->addAction(exitMenu);

    //Info Menu
    QMenu *infoMenu = new QMenu(QMenu::tr("Info"));
    menuBar->addMenu(infoMenu);

    setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{
}
