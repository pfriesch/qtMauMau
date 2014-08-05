#include "soundmanager.h"
#include "QDebug"
#include "settings.h"

SoundManager::SoundManager(QObject *parent) :
    QObject(parent)
{
    player = new QSoundEffect();
    player->setVolume(Settings::getInstance()->getProperty("common/volume").toInt()/100);
}

void SoundManager::playCard()
{
    int random = getRandom(1,4);
    player->setSource(QUrl::fromLocalFile("sound/cardPlace" + QString::number(random) +".wav"));
    player->play();
}

int SoundManager::getRandom(int low, int high){
    return (qrand() % ((high + 1) - low) + low);
}

void SoundManager::drawCard()
{
    int random = getRandom(1,4);
    player->setSource(QUrl::fromLocalFile("sound/cardShove" + QString::number(random) +".wav"));
    player->play();
}

void SoundManager::startSound()
{
    player->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->play();
}

void SoundManager::winnerSound()
{
    player->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    player->play();
}

SoundManager::~SoundManager()
{
    delete player;
}


