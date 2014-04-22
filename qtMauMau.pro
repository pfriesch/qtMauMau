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
    gui/playground.cpp \
    gui/cardviewcontroller.cpp \
    gui/optiondialog.cpp

HEADERS  += mainwindow.h \
    settings.h \
    network/server.h \
    network/client.h \
    gui/playground.h \
    gui/cardviewcontroller.h \
    gui/optiondialog.h

FORMS    += \
    gui/optiondialog.ui


TRANSLATIONS    = qtmaumau_de.ts \

# Decide if its Debug or Release
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

# Copy images,config etc. in the build folder
images.path    = $$DESTDIR/img
images.files   = img/*
config.path    = $$DESTDIR/
config.files   = config.ini
translation.path    = $$DESTDIR/
translation.files   = qtmaumau_de.qm
INSTALLS       += images config translation

