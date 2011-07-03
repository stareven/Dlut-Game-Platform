#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T22:34:17
#
#-------------------------------------------------

QT       += core gui network

TARGET = SnakeClient
TEMPLATE = app
INCLUDEPATH += ../api/include \
				../SnakeCommon/


SOURCES += main/main.cpp\
        gui/mainwindow.cpp \
    ../SnakeCommon/jsnake.cpp \
    gui/jsnakewidget.cpp \
    ../SnakeCommon/jsnakegame.cpp \
	gui/jhallwidget.cpp \
	../api/src/network/jsocketbase.cpp \
    network/jsnakesocket.cpp

HEADERS  += gui/mainwindow.h \
    ../SnakeCommon/jsnake.h \
    gui/jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h \
	gui/jhallwidget.h \
	../api/include/network/jsocketbase.h \
	../api/include/global/jglobal.h \
	../api/include/global/magicnumber.h \
    network/jsnakesocket.h \
    ../SnakeCommon/jsnakeglobal.h

FORMS    += gui/mainwindow.ui \
    gui/jsnakewidget.ui \
    gui/jhallwidget.ui

RESOURCES += \
    res/res.qrc
