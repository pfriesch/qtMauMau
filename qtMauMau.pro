#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T09:38:37
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += testlib
QT       += multimedia
QT       += webkitwidgets


greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET   = qtMauMau
TEMPLATE = app
CONFIG += c++11
CONFIG += testcase
CONFIG += openssl-linked

#DEFINES += TEST

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    network/server.cpp \
    network/client.cpp \
    gameLogic/deck.cpp \
    gameLogic/card.cpp \
    gui/playground.cpp \
    gui/optiondialog.cpp \
    gui/carditem.cpp \
    gui/playeritem.cpp \
    gameLogic/Test/gamecontroller_test.cpp \
    gameLogic/Test/decktest.cpp \
    gui/animatedgraphicsscene.cpp \
    gameLogic/gamecontroller.cpp \
    gameLogic/humanplayer.cpp \
    gameLogic/aiplayer.cpp \
    gameLogic/remoteplayer.cpp \
    gameLogic/player.cpp \
    gameLogic/gamecontrollerproxy.cpp \
    gui/choosecolordialog.cpp \
    gui/connecttoserver.cpp \
    gui/createserverdialog.cpp \
    gui/setnamedialog.cpp \
    gui/soundmanager.cpp \
    network/maumauprotokoll.cpp \
    network/msocket.cpp \
    gameLogic/Test/aiplayer_test.cpp \
    gameLogic/Test/gcproxy_mockup.cpp \
    gui/infodialog.cpp \
    gui/addremoteplayer.cpp \
    gui/gamehistory.cpp \




HEADERS  += mainwindow.h \
    settings.h \
    network/server.h \
    network/client.h \
    gameLogic/gamecontroller.h \
    gameLogic/card.h \
    gameLogic/deck.h \
    gui/playground.h \
    gui/optiondialog.h \
    gui/carditem.h \
    gui/playeritem.h \
    gameLogic/Deck.h \
    gameLogic/Test/gamecontroller_test.h \
    gameLogic/Test/decktest.h \
    gui/animatedgraphicsscene.h \
    gameLogic/player.h \
    gameLogic/humanplayer.h \
    gameLogic/aiplayer.h \
    gameLogic/remoteplayer.h \
    gui/choosecolordialog.h \
    gameLogic/gamecontrollerproxy.h \
    gameLogic/playername.h \
    gui/connecttoserver.h \
    gui/createserverdialog.h \
    gui/setnamedialog.h \
    gui/soundmanager.h \
    network/maumauprotokoll.h \
    network/msocket.h \
    gameLogic/Test/aiplayer_test.h \
    gameLogic/Test/gcproxy_mockup.h \
    gui/infodialog.h \
    gui/addremoteplayer.h\
    gui/gamehistory.h \



FORMS    += \
    gui/optiondialog.ui \
    gui/choosecolordialog.ui \
    gui/connecttoserver.ui \
    gui/createserverdialog.ui \
    gui/setnamedialog.ui \
    gui/infodialog.ui \
    gui/addremoteplayer.ui \


TRANSLATIONS    = qtmaumau_de.ts \


# Decide if its Debug or Release
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

# Copy images,config etc. in the build folder
images.path    = $$DESTDIR/img
images.files   = img/*
sound.path    = $$DESTDIR/sound
sound.files   = sound/*
config.path    = $$DESTDIR/
config.files   = config.ini
translation.path    = $$DESTDIR/
translation.files   = qtmaumau_de.qm
INSTALLS       += images config translation sound

