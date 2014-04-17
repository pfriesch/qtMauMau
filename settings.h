#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <stdlib.h>
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QVariant>

class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings* getInstance();
    void setProperty(QString key, QString value);
    QString getProperty(QString key);
    void showAllKeys();
    ~Settings();

 private:
    explicit Settings(QObject *parent = 0);
    QSettings *settings;


signals:

public slots:

};

#endif // SETTINGS_H
