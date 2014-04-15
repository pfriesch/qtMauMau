#include "mainwindow.h"
#include <QApplication>
#include "network/server.h"
#include "settings.h"

#include <stdlib.h>
#include <QVariant>
#include <stdio.h>
#include <iostream>
#include <string>
#include <network/client.h>
using namespace std;
int main(int argc, char *argv[])
{

      QApplication a(argc, argv);
     QTextStream qtin(stdin);
      QString word;

      std::cout << "So, what do you wanna?" << std::endl;
      qtin >> word;
      if(!word.compare("s")){
          std::cout << "Server" << std::endl;
          Server server();
      }
      if(!word.compare("c")){
          std::cout << "Client" << std::endl;
          Client client();
      }
      std::cout << "Bye" << std::endl;

      MainWindow w;
      w.show();

     return a.exec();
}
