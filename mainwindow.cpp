#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsView>
#include <QBrush>
#include "gui/playground.h"
#include "settings.h"

MainWindow::MainWindow(QWidget* parent)
{
    setupMenuBar();
    setupGraphicsView();
}

/**
 * Setup the View with Cards and setup a new Game
 * @brief MainWindow::setupGraphicsView
 */
void MainWindow::setupGraphicsView()
{
    Playground* scene = new Playground();
    scene->startGame();
    QGraphicsView* view = new QGraphicsView(this);
    scene->setSceneRect(0, 0, Settings::getInstance()->getProperty("common/width").toInt(), Settings::getInstance()->getProperty("common/height").toInt());
    view->setScene(scene);
    setCentralWidget(view);
}

/**
 * Setup the Menubar for the MainWindow
 * @brief MainWindow::setupMenuBar
 */
void MainWindow::setupMenuBar()
{
    QMenuBar* menuBar = new QMenuBar();

    // File Menu
    QMenu* fileMenu = new QMenu(QMenu::tr("File"));
    menuBar->addMenu(fileMenu);

    QAction* startGameMenu = new QAction(QAction::tr("Start Game"), this);
    fileMenu->addAction(startGameMenu);

    QAction* optionsMenu = new QAction(QAction::tr("Options"), this);

    optionDialog = new OptionDialog;
    connect(optionsMenu, SIGNAL(triggered()), optionDialog, SLOT(show()));

    fileMenu->addAction(optionsMenu);

    QAction* exitMenu = new QAction(QAction::tr("Exit"), this);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(exitMenu);

    //Info Menu
    QMenu* infoMenu = new QMenu(QMenu::tr("Info"));
    menuBar->addMenu(infoMenu);

    setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{
}
