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
    playground = new Playground();
    QGraphicsView* view = new QGraphicsView(this);
    playground->setSceneRect(0, 0, this->width() - 50, this->height() - 50);
    view->setScene(playground);
    setCentralWidget(view);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (playground != NULL) {
        playground->setSceneRect(0, 0, event->size().width() - 50, event->size().height() - 50);
        playground->rearrangeLayout();
    }
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

    QAction* startLocalGameMenu = new QAction(QAction::tr("Start Local Game"), this);
    connect(startLocalGameMenu, SIGNAL(triggered()), this, SLOT(startGameAsLocal()));
    fileMenu->addAction(startLocalGameMenu);

    QAction* connectToServerMenu = new QAction(QAction::tr("Connect to Server..."), this);
    fileMenu->addAction(connectToServerMenu);
    connect(connectToServerMenu, SIGNAL(triggered()), this, SLOT(startGameAsClient()));

    QAction* createServerMenu = new QAction(QAction::tr("Create Server..."), this);
    connect(createServerMenu, SIGNAL(triggered()), this, SLOT(startGameAsServer()));
    fileMenu->addAction(createServerMenu);

    QAction* optionsMenu = new QAction(QAction::tr("Options..."), this);

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

void MainWindow::resetGame()
{
}

void MainWindow::connectSignalsForLocal()
{
    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(humanPlayer, &HumanPlayer::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(humanPlayer, &HumanPlayer::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, humanPlayer, &HumanPlayer::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, humanPlayer, &HumanPlayer::UIdrawsCard);
}
/*
void MainWindow::connectSignalsForServer()
{
    // From GameController(Logic) ----> Playground(View)
    QObject::connect(gc, &GameController::initPlayground, playground, &Playground::initPlayground);
    QObject::connect(gc, &GameController::playerDoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(gc, &GameController::playerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(gc, &GameController::addPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(gc, &GameController::playerDrawsCard, playground, &Playground::playerDrawsCard);

    //From Playground(View) ---> GameController(View)
    QObject::connect(playground, &Playground::playCard, gc, &GameController::playCard);
    QObject::connect(playground, &Playground::drawCard, gc, &GameController::drawCard);
}
*/
void MainWindow::startGameAsLocal()
{
    gc = new GameController();
    gc->localGame();
    humanPlayer = static_cast<HumanPlayer*>(gc->getBottomPlayer());
    connectSignalsForLocal();
    playground->startGame();
    gc->gameInit();
}

void MainWindow::startGameAsServer()
{

    server = new Server();
    createServerDialog = new CreateServerDialog;
    connect(server, &Server::newConnection, createServerDialog, &CreateServerDialog::newPlayer);

    createServerDialog->show();
    // resetGame();
    //connectSignalsForServer();
    //playground->startGame();
    //gc = new GameController();
    //gc->gameInit();
}

void MainWindow::startGameAsClient()
{
    client = new Client();
    connectToServer = new ConnectToServer;
    connect(connectToServer, &ConnectToServer::connectToServer, client, &Client::setupConnection);
    connectToServer->show();
}

MainWindow::~MainWindow()
{
}
