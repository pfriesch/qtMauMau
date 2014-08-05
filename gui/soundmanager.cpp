#include "soundmanager.h"
#include "QDebug"

SoundManager::SoundManager(QObject *parent) :
    QObject(parent)
{
    player = new QSoundEffect();
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
    int random = getRandom(1,8);
    player->setSource(QUrl::fromLocalFile("sound/cardSlide" + QString::number(random) +".wav"));
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


