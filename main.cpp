#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTime>
#include <gameLogic/gamecontroller.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QTime>
#include <QObject>
#include <QDesktopWidget>
#include <QStyle>
#include <gui/playground.h>
#include <gameLogic/remoteplayer.h>
#include <network/server.h>
#include <network/client.h>

//#define TEST

#ifdef TEST
#include "gameLogic/Test/gamecontroller_test.h"
#include "gameLogic/Test/decktest.h"
#endif

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message)
{
    QString txt;
    QTime time;
    std::cout << message.toStdString() << std::endl;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug - %1: %2").arg(time.currentTime().toString()).arg(message);
        break;
    case QtWarningMsg:
        txt = QString("Warning - %1: %2").arg(time.currentTime().toString()).arg(message);
        break;
    case QtCriticalMsg:
        txt = QString("Critical - %1: %2").arg(time.currentTime().toString()).arg(message);
        break;
    case QtFatalMsg:
        txt = QString("Fatal - %1: %2").arg(time.currentTime().toString()).arg(message);
        abort();
    }

    QFile outFile("maumau-log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

//void connectSignals(Playground* playground, GameController& gc)
//{
//    // From GameController(Logic) ----> Playground(View)
//    QObject::connect(&gc, &GameController::initPlayground, playground, &Playground::initPlayground);
//    QObject::connect(&gc, &GameController::playerDoTurn, playground, &Playground::playerDoTurn);
//    QObject::connect(&gc, &GameController::playerPlaysCard, playground, &Playground::playerPlaysCard);
//    QObject::connect(&gc, &GameController::addPlayerCard, playground, &Playground::addPlayerCard);
//    QObject::connect(&gc, &GameController::playerDrawsCard, playground, &Playground::playerDrawsCard);

//    //From Playground(View) ---> GameController(View)
//    QObject::connect(playground, &Playground::playCard, &gc, &GameController::playCard);
//    QObject::connect(playground, &Playground::drawCard, &gc, &GameController::drawCard);
//}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //set seed for rand()
    std::time_t t;
    time(&t);
    srand((unsigned int)t);

    if (QFile::exists("maumau-log.txt")) {
        QFile::remove("maumau-log.txt");
    }

    //This should be changeable in the option menu
    QTranslator translator;
    translator.load("qtmaumau_de");
    app.installTranslator(&translator);

    //Lets register our custom debug handler, before we start
    qInstallMessageHandler(customMessageHandler);

    MainWindow window;
    //Center window
    //QDesktopWidget *s = QApplication::desktop();
    window.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            window.size(),
            app.desktop()->availableGeometry()
        ));

    // Anfang Server
    Server *server = new Server();
    RemotePlayer *player = new RemotePlayer(server,1);

    Client *client = new Client();
    client->write();



    // Ende Server

    //Playground* playground = window.getPlayground();
    //GameController gc;
//    connectSignals(playground, gc);
//    gc.gameInit();
    window.show();

#ifdef TEST
    //TODO TEST
    GameControllerTest* gcTest = new GameControllerTest();
    DeckTest* deckTest = new DeckTest();
    QTest::qExec(gcTest);
    QTest::qExec(deckTest);
#endif

    return app.exec();
}
