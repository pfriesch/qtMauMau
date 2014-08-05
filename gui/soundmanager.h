#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    explicit SoundManager(QObject *parent = 0);
    void playCard();
    void drawCard();
    void startSound();
    void winnerSound();
    int getRandom(int low, int high);
    ~SoundManager();

private:
    QSoundEffect *player;
signals:

public slots:

};

#endif // SOUNDMANAGER_H
