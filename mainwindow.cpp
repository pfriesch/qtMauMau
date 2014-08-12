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
    connect(startLocalGameMenu, &QAction::triggered, this, &MainWindow::startGameAsLocal);
    fileMenu->addAction(startLocalGameMenu);

    QAction* connectToServerMenu = new QAction(QAction::tr("Connect to Server..."), this);
    fileMenu->addAction(connectToServerMenu);
    connect(connectToServerMenu, &QAction::triggered, this, &MainWindow::startGameAsClientDialog);

    QAction* createServerMenu = new QAction(QAction::tr("Create Server..."), this);
    connect(createServerMenu, &QAction::triggered, this, &MainWindow::startGameAsServerDialog);
    fileMenu->addAction(createServerMenu);

    QAction* optionsMenu = new QAction(QAction::tr("Options..."), this);

    connect(optionsMenu, &QAction::triggered, this, &MainWindow::showOptionDialog);

    fileMenu->addAction(optionsMenu);

    QAction* exitMenu = new QAction(QAction::tr("Exit"), this);
    connect(exitMenu, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitMenu);

    //Info Menu
    QMenu* infoMenu = new QMenu(QMenu::tr("Info"));
    menuBar->addMenu(infoMenu);

    setMenuBar(menuBar);
}

void MainWindow::resetGame()
{
}

void MainWindow::connectSignalsForLocal(HumanPlayer* humanPlayer)
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

void MainWindow::connectSignalsForServer(HumanPlayer* humanPlayer, QVector<RemotePlayer*> remotePlayers)
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
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteInitPlayground, server, &MauServer::RemoteInitPlayground);
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteDoTurn, server, &MauServer::RemoteDoTurn);
        QObject::connect(_remotePlayer, &RemotePlayer::RemotePlayerPlaysCard, server, &MauServer::RemotePlayerPlaysCard);
        QObject::connect(_remotePlayer, &RemotePlayer::RemotePlayerDrawsCard, server, &MauServer::RemotePlayerDrawsCard);
        QObject::connect(_remotePlayer, &RemotePlayer::RemoteAddPlayerCard, server, &MauServer::RemoteAddPlayerCard);
        QObject::connect(_remotePlayer, &RemotePlayer::RemotePlayerWon, server, &MauServer::RemotePlayerWon);

        // From  Server(Network) ----> RemotePlayer(Logic)
        QObject::connect(server, &MauServer::RemotePlaysCard, _remotePlayer, &RemotePlayer::RemotePlaysCard);
        QObject::connect(server, &MauServer::RemoteDrawsCard, _remotePlayer, &RemotePlayer::RemoteDrawsCard);
    }
}

void MainWindow::connectSignalsForClient()
{
    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(client, &MauClient::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(client, &MauClient::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(client, &MauClient::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(client, &MauClient::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(client, &MauClient::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, client, &MauClient::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, client, &MauClient::UIdrawsCard);
}

void MainWindow::startGameAsLocal()
{
    resetGame();
    gc = new GameController();
    gc->localGame();
    connectSignalsForLocal(static_cast<HumanPlayer*>(gc->getBottomPlayer()));
    playground->startGame();

    if (Settings::getInstance()->contains("game/draw2xCard")) {
        gc->gameInit(Card::cardValue(Settings::getInstance()->getProperty("game/draw2xCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/wishSuitCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/skipNextCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/changeDirectCard").toInt()));
    } else {
        gc->gameInit();
    }
}

void MainWindow::startGameAsServerDialog()
{

    server = new MauServer();
    createServerDialog = new CreateServerDialog;
    QObject::connect(server, &MauServer::newConnection, createServerDialog, &CreateServerDialog::newPlayer);
    QObject::connect(createServerDialog, &CreateServerDialog::startNetworkGame, this, &MainWindow::startNetworkGame);
    createServerDialog->setModal(true);
    createServerDialog->show();
}

void MainWindow::startNetworkGame(QVector<QPair<Player::Type, int> > players)
{
    resetGame();

    playground->startGame();
    gc = new GameController();
    std::vector<Player*> _players;
    QVector<RemotePlayer*> remotePlayers;
    for (int i = 0; i < players.size(); ++i) {
        if (players.at(i).first == Player::AI_PLAYER) {
            _players.push_back(new AIPlayer(PLAYER::Name(i + 1), GameControllerProxy(gc, PLAYER::Name(i + 1))));
        } else if (players.at(i).first == Player::REMOTE_PLAYER) {
            _players.push_back(new RemotePlayer(PLAYER::Name(i + 1), GameControllerProxy(gc, PLAYER::Name(i + 1))));
            remotePlayers.append(static_cast<RemotePlayer*>(_players.back()));
        }
    }
    gc->networkGame(_players);
    connectSignalsForServer(static_cast<HumanPlayer*>(gc->getBottomPlayer()), remotePlayers);
    createServerDialog->hide();
    playground->startGame();

    if (Settings::getInstance()->contains("game/draw2xCard")) {
        gc->gameInit(Card::cardValue(Settings::getInstance()->getProperty("game/draw2xCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/wishSuitCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/skipNextCard").toInt()),
                     Card::cardValue(Settings::getInstance()->getProperty("game/changeDirectCard").toInt()));
    } else {
        gc->gameInit();
    }
}

void MainWindow::startGameAsClient()
{
    resetGame();
    playground->startGame();
    connectSignalsForClient();
}

void MainWindow::startGameAsClientDialog()
{
    resetGame();
    client = new MauClient();
    connectToServer = new ConnectToServer;
    QObject::connect(connectToServer, &ConnectToServer::connectToServer, client, &MauClient::setupConnection);
    QObject::connect(client, &MauClient::clientGameStarted, connectToServer, &ConnectToServer::clientGameStarted);
    QObject::connect(client, &MauClient::clientGameStarted, this, &MainWindow::startGameAsClient);
    connectToServer->setModal(true);
    connectToServer->show();
}

void MainWindow::showOptionDialog()
{
    optionDialog = new OptionDialog;
    optionDialog->setModal(true);
    optionDialog->show();
}

MainWindow::~MainWindow()
{
}
