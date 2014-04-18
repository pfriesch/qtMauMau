#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTime>

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &message)
{
    QString txt;
    QTime time;
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


int main(int argc, char *argv[])
{

      QApplication app(argc, argv);

      if (QFile::exists("maumau-log.txt")) {
          QFile::remove("maumau-log.txt");
      }

      //This should be changeable in the option menu
      QTranslator translator;
      translator.load("qtmaumau_de");
      //app.installTranslator(&translator);

      //Lets register our custom debug handler, before we start
      qInstallMessageHandler(customMessageHandler);

      MainWindow window;
      window.show();

      return app.exec();
}
