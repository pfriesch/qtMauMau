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
    this->setFixedWidth(Settings::getInstance()->getProperty("common/width").toInt());
    this->setFixedHeight(Settings::getInstance()->getProperty("common/height").toInt());
    setupMenuBar();
    setupGraphicsView();
}

/**
 * Setup the View with Cards and setup a new Game
 * @brief MainWindow::setupGraphicsView
 */
void MainWindow::setupGraphicsView()
{
    playground = new Playground();
    QGraphicsView* view = new QGraphicsView(this);
    playground->setSceneRect(0,0, Settings::getInstance()->getProperty("common/width").toInt()-50, Settings::getInstance()->getProperty("common/height").toInt()-50);
    playground->startGame();
    view->setScene(playground);
    setCentralWidget(view);
}
Playground *MainWindow::getPlayground() const
{
    return playground;
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
