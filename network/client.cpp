#include "client.h"
#include <QHostAddress>
#include <settings.h>

Client::Client(QObject* parent): QObject(parent)
{
  connect(&client, SIGNAL(connected()),this, SLOT(write()));
}

void Client::setupConnection(QHostAddress address)
{
  int port(Settings::getInstance()->getProperty("network/port").toInt());

  client.connectToHost(address, port);

  if(client.error()){
    qCritical() << client.error();
    qCritical() << client.errorString();
  }
}

void Client::write()
{
  //write HelloWorld is just a dummy
  client.write("Hello, world", 13);
}

Client::~Client()
{
  client.close();
}
