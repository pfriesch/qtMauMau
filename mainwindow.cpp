#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsView>
#include <QBrush>
#include "gui/playground.h"
#include "settings.h"
#include "gui/setnamedialog.h"
MainWindow::MainWindow(QWidget* parent)
{
    setupMenuBar();
    setupGraphicsView();
    //if(Settings::getInstance()->getProperty("common/changed_playername").toInt(0,10) == 0){
    //    showNameDialog();
    //}
}

void MainWindow::showNameDialog()
{
    //    SetNameDialog *dialog = new SetNameDialog();
    //    dialog->setModal(true);
    //    dialog->show();
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

    connect(optionsMenu, SIGNAL(triggered()), this, SLOT(showOptionDialog()));

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

void MainWindow::connectSignalsForServer(std::vector<Player*> remotePlayers)
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

    foreach(Player * remotePlayer, remotePlayers)
    {
        RemotePlayer* _remotePlayer = static_cast<RemotePlayer*>(remotePlayer);
        // From RemotePlayer(Logic) ----> Server(Network)
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteInitPlayground, server, &Server::RemoteInitPlayground);
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteDoTurn, server, &Server::RemoteDoTurn);
        QObject::connect(_remotePlayer, &RemotePlayer::RemotePlayerPlaysCard, server, &Server::RemotePlayerPlaysCard);
        QObject::connect(_remotePlayer, &RemotePlayer::RemotePlayerDrawsCard, server, &Server::RemotePlayerDrawsCard);
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteAddPlayerCard, server, &Server::RemoteAddPlayerCard);

        // From  Server(Network) ----> RemotePlayer(Logic)
        QObject::connect(server, &Server::RemotePlaysCard, _remotePlayer, &RemotePlayer::RemotePlaysCard);
        QObject::connect(server, &Server::RemoteDrawsCard, _remotePlayer, &RemotePlayer::RemoteDrawsCard);
    }
}

void MainWindow::connectSignalsForClient()
{
    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(client, &Client::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(client, &Client::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(client, &Client::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(client, &Client::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(client, &Client::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, client, &Client::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, client, &Client::UIdrawsCard);
}

void MainWindow::startGameAsLocal()
{
    resetGame();
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
    QObject::connect(server, &Server::newConnection, createServerDialog, &CreateServerDialog::newPlayer);
    QObject::connect(createServerDialog, &CreateServerDialog::startNetworkGame, this, &MainWindow::startNetworkGame);
    createServerDialog->show();
}

void MainWindow::startNetworkGame()
{
    resetGame();

    playground->startGame();
    gc = new GameController();

    std::vector<Player*> remotePlayers;
    for (int i = 0; i < server->getClients().size(); ++i) {
        remotePlayers.push_back(new RemotePlayer(PLAYER::Name(i + 1), GameControllerProxy(gc, PLAYER::Name(i + 1))));
    }
    gc->networkGame(remotePlayers);
    humanPlayer = static_cast<HumanPlayer*>(gc->getBottomPlayer());
    connectSignalsForServer(remotePlayers);
    createServerDialog->hide();
    playground->startGame();
    gc->gameInit();
}

void MainWindow::startGameAsClient()
{
    resetGame();
    client = new Client();
    connectToServer = new ConnectToServer;
    QObject::connect(connectToServer, &ConnectToServer::connectToServer, client, &Client::setupConnection);
    QObject::connect(client, &Client::gameStarted, connectToServer, &ConnectToServer::gameStarted);
    connectToServer->show();
}

void MainWindow::showOptionDialog()
{
    optionDialog = new OptionDialog;
    optionDialog->show();
}

MainWindow::~MainWindow()
{
}
