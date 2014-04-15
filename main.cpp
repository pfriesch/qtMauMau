#include "mainwindow.h"
#include <QApplication>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &message)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(message);
        break;

    case QtWarningMsg:
        txt = QString("Warning: %1").arg(message);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(message);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(message);
        abort();
    }

    QFile outFile("maumau-log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}


int main(int argc, char *argv[])
{

      QApplication a(argc, argv);

      //Lets register our custom debug handler, before we start
      qInstallMessageHandler(customMessageHandler);

      MainWindow w;
      w.show();

      return a.exec();
}
