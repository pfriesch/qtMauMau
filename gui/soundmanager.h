#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QSound>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    explicit SoundManager(QObject *parent = 0);
    void playCard();
    void drawCard();
    void startSound();
    void playBackgroundSong();
    void winnerSound();
    int getRandom(int low, int high);
    ~SoundManager();

private:
    QMediaPlayer *player;
    QSoundEffect *effect;
signals:

private slots:
    void stateChanged(QMediaPlayer::State state);

public slots:

};

#endif // SOUNDMANAGER_H
