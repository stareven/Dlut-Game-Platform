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
    network/jsnakesocket.cpp \
    service/jglobalsettings.cpp \
    ../api/src/service/jrequestuserinfo.cpp \
    ../api/src/service/jplhrequestbase.cpp \
    ../api/src/service/jrequestbase.cpp \
    ../api/src/network/jrequestuserinfosocket.cpp \
    ../api/src/network/jplhsocketbase.cpp \
    ../api/src/network/jsocketbase.cpp \
    ../api/src/global/userinfo.cpp \
    ../api/src/service/jrequestport.cpp \
    ../api/src/network/jrequestportsocket.cpp \
    ../api/src/global/shost.cpp \
    ../api/src/service/jcryprorecorder.cpp \
    ../SnakeCommon/jsnakestream.cpp
    
HEADERS  += gui/mainwindow.h \
    ../SnakeCommon/jsnake.h \
    gui/jsnakewidget.h \
    ../SnakeCommon/jsnakegame.h \
	gui/jhallwidget.h \
	../api/include/global/jglobal.h \
	../api/include/global/magicnumber.h \
    network/jsnakesocket.h \
    ../SnakeCommon/jsnakeglobal.h \
    service/jglobalsettings.h \
    ../api/include/global/eportsrv.h \
    ../api/include/service/jrequestuserinfo.h \
    ../api/include/service/jplhrequestbase.h \
    ../api/include/service/jrequestbase.h \
    ../api/include/network/jrequestuserinfosocket.h \
    ../api/include/network/jplhsocketbase.h \
    ../api/include/network/jsocketbase.h \
    ../api/include/global/userinfo.h \
    ../api/include/service/jrequestport.h \
    ../api/include/network/jrequestportsocket.h \
    ../api/include/service/jcryprorecorder.h
    
FORMS    += gui/mainwindow.ui \
    gui/jsnakewidget.ui \
    gui/jhallwidget.ui

RESOURCES += \
    res/res.qrc
