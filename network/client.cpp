#include "client.h"

Client::Client(QObject* parent): QObject(parent)
{
  connect(&client, SIGNAL(connected()),this, SLOT(startTransfer()));
}

void Client::start(QString address, quint16 port)
{
  QHostAddress addr(address);
  client.connectToHost(addr, port);
}

void Client::startTransfer()
{
  client.write("Hello, world from Berlin", 13);
}

Client::~Client()
{
  client.close();
}
