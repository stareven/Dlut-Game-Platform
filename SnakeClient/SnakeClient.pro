#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T22:34:17
#
#-------------------------------------------------

QT       += core gui

TARGET = SnakeClient
TEMPLATE = app


SOURCES += main/main.cpp\
        gui/mainwindow.cpp \
    ../SnakeCommon/jsnake.cpp \
    gui/jsnakewidget.cpp \
    ../SnakeCommon/jsnakegame.cpp \
    gui/jhallwidget.cpp

HEADERS  += gui/mainwindow.h \
    ../SnakeCommon/jsnake.h \
    gui/jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h \
    gui/jhallwidget.h

FORMS    += gui/mainwindow.ui \
    gui/jsnakewidget.ui \
    gui/jhallwidget.ui

RESOURCES += \
    res/res.qrc
