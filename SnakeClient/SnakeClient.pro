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
    ../SnakeCommon/jsnakegame.cpp \
    jhallwidget.cpp

HEADERS  += mainwindow.h \
    ../SnakeCommon/jsnake.h \
    jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h \
    jhallwidget.h

FORMS    += mainwindow.ui \
    jsnakewidget.ui \
    jhallwidget.ui

RESOURCES += \
    res.qrc
