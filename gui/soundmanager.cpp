#include "soundmanager.h"
#include "QDebug"
#include "settings.h"

SoundManager::SoundManager(QObject* parent)
    : QObject(parent)
{
    player = new QMediaPlayer();
    effect = new QSoundEffect();

    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));

    int volume = Settings::getInstance()->getProperty("common/volume").toInt();

    player->setVolume(volume);
    effect->setVolume((float)volume / 100);
}

void SoundManager::playCard()
{
    int random = getRandom(1, 4);

    effect->setSource(QUrl::fromLocalFile("sound/cardPlace" + QString::number(random) + ".wav"));
    effect->play();
}

int SoundManager::getRandom(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

void SoundManager::drawCard()
{
    int random = getRandom(1, 4);
    effect->setSource(QUrl::fromLocalFile("sound/cardShove" + QString::number(random) + ".wav"));
    effect->play();
}

void SoundManager::startSound()
{
    effect->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    effect->play();
}

void SoundManager::winnerSound()
{
    effect->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    effect->play();
}

void SoundManager::playBackgroundSong()
{
    if (Settings::getInstance()->getProperty("common/background_music").toInt() == 1) {
        player->setMedia(QUrl::fromLocalFile("sound/hansatom.mp3"));
        player->play();
    }
}

SoundManager::~SoundManager()
{
    delete effect;
    delete player;
}

void SoundManager::stateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState) {
        player->play();
    }
}
