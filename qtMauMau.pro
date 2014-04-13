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

SOURCES += main.cpp\
        mainwindow.cpp \
    network/networkmanager.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    network/networkmanager.h \
    settings.h

FORMS    += mainwindow.ui

OTHER_FILES += \
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


