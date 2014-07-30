#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QTime>
#include <QObject>
#include <QDesktopWidget>
#include <QStyle>
#include <network/server.h>
#include <network/client.h>
#include <gui/playground.h>
#include <settings.h>

#include "gameLogic/humanplayer.h"

//#define TEST

#ifdef TEST
#include "gameLogic/Test/gamecontroller_test.h"
#include "gameLogic/Test/decktest.h"
#endif

Client* client;

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
    translator.load(Settings::getInstance()->getProperty("common/language"));
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
            QSize(Settings::getInstance()->getProperty("common/width").toInt(), Settings::getInstance()->getProperty("common/height").toInt()),
            app.desktop()->availableGeometry()));

    // Anfang Server
    //Server *server = new Server();
    //RemotePlayer *player = new RemotePlayer(server,1);

    //client = new Client();
    //client->setupConnection(QHostAddress("192.168.0.150"));
    //client->write();

    // Ende Server

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
