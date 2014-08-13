#ifndef AIPLAYER_TEST_H
#define AIPLAYER_TEST_H

#include <QObject>
#include <QTest>
#include "gameLogic/aiplayer.h"
#include "gameLogic/Test/gcproxy_mockup.h"

class AIPlayer_test : public QObject {

    Q_OBJECT
private:

private
slots:
    void initTestCase()
    {
    }
    void myFirstTest()
    {
        QVERIFY(1 == 1);
    }
    void cleanupTestCase()
    {
        qDebug("called after myFirstTest and mySecondTest");
    }
};

#endif // AIPLAYER_TEST_H
