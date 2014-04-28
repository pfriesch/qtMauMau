#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject* parent = 0);
    ~Client();
    void setupConnection(QHostAddress address);
public
slots:
    void write();

private:
    QTcpSocket client;
};
