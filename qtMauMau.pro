#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T09:38:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtMauMau
TEMPLATE = app
CONFIG += c++11

QT += network

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    network/server.cpp \
    network/client.cpp \
    gameLogic/Card.cpp \
    gameLogic/Deck.cpp \
    gameLogic/player.cpp \
    gameLogic/gamecontroller.cpp

HEADERS  += mainwindow.h \
    settings.h \
    network/server.h \
    network/client.h \
    gameLogic/Card.h \
    gameLogic/Deck.h \
    gameLogic/player.h \
    gameLogic/gamecontroller.h

FORMS    +=


TRANSLATIONS    = qtmaumau_de.ts \

OTHER_FILES += \
    config.ini \
    config.ini

# Copy ini file post build
win32 {
    DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN = $${PWD}
    PWD_WIN ~= s,/,\\,g
    for(FILE, OTHER_FILES){
        QMAKE_POST_LINK += $$quote(cmd /c copy /y $${PWD_WIN}\\$${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
    }
}
unix {
    for(FILE, OTHER_FILES){
        QMAKE_POST_LINK += $$quote(cp $${PWD}/$${FILE} $${DESTDIR}$$escape_expand(\\n\\t))
}
}


