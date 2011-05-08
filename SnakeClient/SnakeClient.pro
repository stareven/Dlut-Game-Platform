#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T22:34:17
#
#-------------------------------------------------

QT       += core gui

TARGET = SnakeClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../SnakeCommon/jsnake.cpp \
    jsnakewidget.cpp \
    ../SnakeCommon/jsnakegame.cpp

HEADERS  += mainwindow.h \
    ../SnakeCommon/jsnake.h \
    jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h

FORMS    += mainwindow.ui \
    jsnakewidget.ui

RESOURCES += \
    res.qrc
