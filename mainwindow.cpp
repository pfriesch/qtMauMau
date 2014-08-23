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
    : QMainWindow(parent)
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
    if (playground != NULL) {
        delete playground;
    }
    if (gc != NULL) {
        delete gc;
    }

    playground = new Playground();
    view = new QGraphicsView(this);
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
    QMenuBar* menuBar = new QMenuBar(this);

    // File Menu
    QMenu* fileMenu = new QMenu(QMenu::tr("File"), this);
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
    QMenu* infoMenu = new QMenu(QMenu::tr("Info"), this);
    menuBar->addMenu(infoMenu);

    QAction* aboutMenu = new QAction(QAction::tr("About"), this);
    connect(aboutMenu, SIGNAL(triggered()), this, SLOT(aboutDialog()));
    infoMenu->addAction(aboutMenu);

    QAction* toggleFullscreen = new QAction(QAction::tr("Toggle Fullscreen"), this);
    connect(toggleFullscreen, &QAction::triggered, this, &MainWindow::toggleFullscreen);
    infoMenu->addAction(toggleFullscreen);

    setMenuBar(menuBar);
}
/**
 * @brief MainWindow::connectSignalsForLocal connects signal for a local game
 * @param humanPlayer
 */
void MainWindow::connectSignalsForLocal(HumanPlayer* humanPlayer)
{
    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(humanPlayer, &HumanPlayer::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(humanPlayer, &HumanPlayer::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIPlayerWon, playground, &Playground::playerWon);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, humanPlayer, &HumanPlayer::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, humanPlayer, &HumanPlayer::UIdrawsCard);
}
/**
 * @brief MainWindow::connectSignalsForServer connect signals for a network game in the server role
 * @param humanPlayer
 * @param remotePlayers
 */
void MainWindow::connectSignalsForServer(HumanPlayer* humanPlayer, QVector<RemotePlayer*> remotePlayers)
{

    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(humanPlayer, &HumanPlayer::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(humanPlayer, &HumanPlayer::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);
    QObject::connect(humanPlayer, &HumanPlayer::UIPlayerWon, playground, &Playground::playerWon);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, humanPlayer, &HumanPlayer::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, humanPlayer, &HumanPlayer::UIdrawsCard);

    foreach(RemotePlayer * remotePlayer, remotePlayers)
    {
        server->dumpObjectInfo();

        // From RemotePlayer(Logic) ----> Server(Network)
        QObject::connect(remotePlayer, &RemotePlayer::RemoteInitPlayground, server, &MauServer::RemoteInitPlayground);
        QObject::connect(remotePlayer, &RemotePlayer::RemoteDoTurn, server, &MauServer::RemoteDoTurn);
        QObject::connect(remotePlayer, &RemotePlayer::RemotePlayerPlaysCard, server, &MauServer::RemotePlayerPlaysCard);
        QObject::connect(remotePlayer, &RemotePlayer::RemotePlayerDrawsCard, server, &MauServer::RemotePlayerDrawsCard);
        QObject::connect(remotePlayer, &RemotePlayer::RemoteAddPlayerCard, server, &MauServer::RemoteAddPlayerCard);
        QObject::connect(remotePlayer, &RemotePlayer::RemotePlayerWon, server, &MauServer::RemotePlayerWon);
        // From  Server(Network) ----> RemotePlayer(Logic)
        QObject::connect(server, &MauServer::RemotePlaysCard, remotePlayer, &RemotePlayer::RemotePlaysCard);
        QObject::connect(server, &MauServer::RemoteDrawsCard, remotePlayer, &RemotePlayer::RemoteDrawsCard);
    }
}
/**
 * @brief MainWindow::connectSignalsForClient connects signals for a network game in the client role
 */
void MainWindow::connectSignalsForClient()
{
    // From HumandPlayer(Logic) ----> Playground(View)
    QObject::connect(client, &MauClient::UIinitPlayground, playground, &Playground::initPlayground);
    QObject::connect(client, &MauClient::UIdoTurn, playground, &Playground::playerDoTurn);
    QObject::connect(client, &MauClient::UIplayerPlaysCard, playground, &Playground::playerPlaysCard);
    QObject::connect(client, &MauClient::UIaddPlayerCard, playground, &Playground::addPlayerCard);
    QObject::connect(client, &MauClient::UIplayerDrawsCard, playground, &Playground::playerDrawsCard);
    QObject::connect(client, &MauClient::UIPlayerWon, playground, &Playground::playerWon);

    //From Playground(View) ---> HumanPlayer(Logic)
    QObject::connect(playground, &Playground::playCard, client, &MauClient::UIplaysCard);
    QObject::connect(playground, &Playground::drawCard, client, &MauClient::UIdrawsCard);
}
/**
 * @brief MainWindow::startGameAsLocal initializes a game as a local game
 */
void MainWindow::startGameAsLocal()
{
    setupGraphicsView();
    gc = new GameController();
    QString humanPlayerName = Settings::getInstance()->getProperty("common/playername");

    QStringList playerNames = { tr("Player 1"), tr("Player 2"), tr("Player 3") };

    std::vector<Player*> players;
    players.push_back(new HumanPlayer(PLAYER::Name::BOTTOM, GameControllerProxy(gc, PLAYER::Name::BOTTOM), humanPlayerName.toStdString()));
    for (int i = 1; i < 4; ++i) {
        players.push_back(new AIPlayer(PLAYER::Name(i), GameControllerProxy(gc, PLAYER::Name(i)), playerNames.at(i - 1).toStdString()));
    }
    gc->setPlayers(players);
    connectSignalsForLocal(static_cast<HumanPlayer*>(players.at(0)));
    playground->startGame();
    try
    {
        if (Settings::getInstance()->contains("game/draw2xCard")) {
            gc->gameInit(Card::cardValue(Settings::getInstance()->getProperty("game/draw2xCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/wishSuitCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/skipNextCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/changeDirectCard").toInt()));
        } else {
            gc->gameInit();
        }
    }
    catch (std::exception e)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("An logical game error occured while playing. This should never happen.\nBut when it does the game can't continue and you need to start a new game"));
        msgBox.exec();
    }
}
/**
 * @brief MainWindow::startGameAsServerDialog initializes a creat server dialog
 */
void MainWindow::startGameAsServerDialog()
{
    if (server != NULL) {
        delete server;
    }
    if (client != NULL) {
        delete client;
    }
    server = new MauServer();
    createServerDialog = new CreateServerDialog;
    QObject::connect(server, &MauServer::newConnection, createServerDialog, &CreateServerDialog::newPlayer);
    QObject::connect(createServerDialog, &CreateServerDialog::startNetworkGame, this, &MainWindow::startNetworkGame);
    QObject::connect(createServerDialog, &CreateServerDialog::playerAccepted, server, &MauServer::acceptConnection);
    QObject::connect(createServerDialog, &CreateServerDialog::playerRejected, server, &MauServer::rejectConnection);

    createServerDialog->setModal(true);
    createServerDialog->show();
}
/**
 * @brief MainWindow::startNetworkGame initializes network game in the server role
 * @param players
 * @param otherPlayerNames
 */
void MainWindow::startNetworkGame(QVector<Player::Type> players, QStringList otherPlayerNames)
{
    setupGraphicsView();
    QString humanPlayerName = Settings::getInstance()->getProperty("common/playername");
    playground->startGame();
    gc = new GameController();
    std::vector<Player*> _players;
    QVector<RemotePlayer*> remotePlayers;

    _players.push_back(new HumanPlayer(PLAYER::Name::BOTTOM, GameControllerProxy(gc, PLAYER::Name::BOTTOM), humanPlayerName.toStdString()));
    for (int i = 0; i < players.size(); ++i) {
        if (players.at(i) == Player::AI_PLAYER) {
            _players.push_back(new AIPlayer(PLAYER::Name(i + 1), GameControllerProxy(gc, PLAYER::Name(i + 1)), otherPlayerNames.at(i).toStdString()));
        } else if (players.at(i) == Player::REMOTE_PLAYER) {
            _players.push_back(new RemotePlayer(PLAYER::Name(i + 1), GameControllerProxy(gc, PLAYER::Name(i + 1)), otherPlayerNames.at(i).toStdString()));
            remotePlayers.append(static_cast<RemotePlayer*>(_players.back()));
        }
    }
    connectSignalsForServer(static_cast<HumanPlayer*>(_players.at(0)), remotePlayers);
    gc->setPlayers(_players);
    createServerDialog->hide();
    playground->startGame();
    try
    {
        if (Settings::getInstance()->contains("game/draw2xCard")) {
            gc->gameInit(Card::cardValue(Settings::getInstance()->getProperty("game/draw2xCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/wishSuitCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/skipNextCard").toInt()),
                         Card::cardValue(Settings::getInstance()->getProperty("game/changeDirectCard").toInt()));
        } else {
            gc->gameInit();
        }
    }
    catch (std::exception e)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("An logical game error occured while playing. This should never happen.\nBut when it does the game can't continue and you need to start a new game"));
        msgBox.exec();
    }
}
/**
 * @brief MainWindow::startGameAsClient initializes game in the client role
 */
void MainWindow::startGameAsClient()
{
    setupGraphicsView();
    playground->startGame();
    connectSignalsForClient();
}
/**
 * @brief MainWindow::startGameAsClientDialog initializes the connect to server dialog
 */
void MainWindow::startGameAsClientDialog()
{
    setupGraphicsView();
    client = new MauClient();
    connectToServer = new ConnectToServer;
    QObject::connect(connectToServer, &ConnectToServer::connectToServer, client, &MauClient::setupConnection);
    QObject::connect(client, &MauClient::clientGameStarted, connectToServer, &ConnectToServer::clientGameStarted);
    QObject::connect(client, &MauClient::clientGameStarted, this, &MainWindow::startGameAsClient);
    QObject::connect(client, &MauClient::connectionAccepted, connectToServer, &ConnectToServer::connectionAccepted);
    QObject::connect(client, &MauClient::connectionRejected, connectToServer, &ConnectToServer::connectionRejected);
    connectToServer->setModal(true);
    connectToServer->show();
}

void MainWindow::showOptionDialog()
{
    optionDialog = new OptionDialog;
    optionDialog->setModal(true);
    optionDialog->show();
}

void MainWindow::aboutDialog()
{
    infoDialog = new InfoDialog();
    infoDialog->setModal(true);
    infoDialog->show();
}

void MainWindow::toggleFullscreen()
{
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

MainWindow::~MainWindow()
{
    if (playground != NULL)
        delete playground;
    if (gc != NULL)
        delete gc;
    if (optionDialog != NULL)
        delete optionDialog;
    if (connectToServer != NULL)
        delete connectToServer;
    if (createServerDialog != NULL)
        delete createServerDialog;
    if (infoDialog != NULL)
        delete infoDialog;
    if (server != NULL)
        delete server;
    if (client != NULL)
        delete client;
    if (view != NULL)
        delete view;
}
