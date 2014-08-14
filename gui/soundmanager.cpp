#include "soundmanager.h"
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

/**
 * If a player plays a card, we play a sound, we have 4 sounds and we choose them randomly
 * @brief SoundManager::playCard
 */
void SoundManager::playCard()
{
    int random = getRandom(1, 4);

    effect->setSource(QUrl::fromLocalFile("sound/cardPlace" + QString::number(random) + ".wav"));
    effect->play();
}

/**
 * create random numbers from low to high
 * @brief SoundManager::getRandom
 * @param low
 * @param high
 * @return
 */
int SoundManager::getRandom(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

/**
 * If a player draws a card, we play a sound
 * @brief SoundManager::drawCard
 */
void SoundManager::drawCard()
{
    int random = getRandom(1, 4);
    effect->setSource(QUrl::fromLocalFile("sound/cardShove" + QString::number(random) + ".wav"));
    effect->play();
}

/**
 * This is our start sound, its a special sound if the game begins
 * @brief SoundManager::startSound
 */
void SoundManager::startSound()
{
    effect->setSource(QUrl::fromLocalFile("sound/cardShuffle.wav"));
    effect->play();
}

void SoundManager::winnerSound()
{
    effect->setSource(QUrl::fromLocalFile("sound/fanfare.wav"));
    effect->play();
}

/**
 * If you opt-in the background music, we start playing it here
 * @brief SoundManager::playBackgroundSong
 */
void SoundManager::playBackgroundSong()
{
    if (Settings::getInstance()->getProperty("common/background_music").toInt() == 1) {
        player->setMedia(QUrl::fromLocalFile("sound/hansatom.mp3"));
        player->play();
    }
}
/**
 * If the background song has ended, we start it again and again and again...again...againg
 * @brief SoundManager::stateChanged
 * @param state
 */
void SoundManager::stateChanged(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState) {
        player->play();
    }
}
SoundManager::~SoundManager(){
    effect->stop();
    player->stop();
    delete effect;
    delete player;
}
