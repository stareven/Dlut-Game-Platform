#-------------------------------------------------
#
# Project created by QtCreator 2011-04-12T22:34:17
#
#-------------------------------------------------

QT       += network

TARGET = SnakeClient
TEMPLATE = app
INCLUDEPATH += \
				../SnakeCommon/

include(../api/api.pri)
QMAKE_RPATHDIR = ../api/lib

SOURCES += main/main.cpp\
        gui/mainwindow.cpp \
    ../SnakeCommon/jsnake.cpp \
    gui/jsnakewidget.cpp \
    ../SnakeCommon/jsnakegame.cpp \
	gui/jhallwidget.cpp \
    network/jsnakesocket.cpp \
	service/jglobalsettings.cpp \
	../SnakeCommon/jsnakestream.cpp \
    service/jroomlistmodel.cpp \
    network/jsnakeprocessor.cpp
    
HEADERS  += gui/mainwindow.h \
    ../SnakeCommon/jsnake.h \
    gui/jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h \
	gui/jhallwidget.h \
    network/jsnakesocket.h \
    ../SnakeCommon/jsnakeglobal.h \
    service/jglobalsettings.h \
    service/jroomlistmodel.h \
    network/jsnakeprocessor.h
    
FORMS    += gui/mainwindow.ui \
    gui/jsnakewidget.ui \
    gui/jhallwidget.ui

RESOURCES += \
	res/res.qrc
