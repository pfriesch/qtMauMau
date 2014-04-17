#include "settings.h"

Settings *instance;
// config.ini should store all the additional configurations
const QString configPath("config.ini");

Settings::Settings(QObject *parent) : QObject(parent)
{
    QFile configFile(configPath);
    if(configFile.exists()){
        this->settings = new QSettings(configFile.fileName(), QSettings::IniFormat);
    }
    else {
        this->settings = new QSettings();
        qCritical() << "Error, can't read config file";
    }
}

/**
 * This is a Singleton class, so beware, there's only one instance
 * from this class.
 * @brief Settings::getInstance
 * @return
 */
Settings* Settings::getInstance(){
    if(!instance){
        instance = new Settings();
    }
    return instance;
}

void Settings::setProperty(const QString key, const QString value){
    settings->setProperty(key.toStdString().c_str(),value);
}

/**
 * Default return value is "" (Empty String) if the key isn't found.
 * Maybe the empty String isn't the best idea, dont know at this point.
 * @brief Settings::getProperty
 * @param key
 * @return
 */
QString Settings::getProperty(const QString key){
    return this->settings->value(key,"").toString();
}

void Settings::showAllKeys(){
    for( QString key : settings->allKeys()){
        qDebug() << key;
    }
}

Settings::~Settings(){
    delete settings;
    delete instance;
}
