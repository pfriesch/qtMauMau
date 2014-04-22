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
    gameLogic/gamecontroller.cpp \
    gameLogic/player.cpp \
    gameLogic/deck.cpp \
    gameLogic/card.cpp
    gui/playground.cpp \
    gui/cardviewcontroller.cpp


HEADERS  += mainwindow.h \
    settings.h \
    network/server.h \
    network/client.h \
    gameLogic/gamecontroller.h \
    gameLogic/player.h \
    gameLogic/card.h \
    gameLogic/deck.h
    gui/playground.h \
    gui/cardviewcontroller.h


FORMS    +=


TRANSLATIONS    = qtmaumau_de.ts \


# Decide if its Debug or Release
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

# Copy images,config etc. in the build folder
images.path    = $$DESTDIR/img
images.files   = img/*
config.path    = $$DESTDIR/
config.files   = config.ini
INSTALLS       += images config

