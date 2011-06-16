#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T17:24:46
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = GameFileServer1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../api/include

SOURCES += main/main.cpp \
    ../api/src/network/jserverbase.cpp \
    ../api/src/network/jconnectionbase.cpp \
    network/jgfsconnection.cpp \
	../api/src/network/jloginsocket.cpp \
	../api/src/network/jportsocket.cpp \
	../api/src/network/jsocketbase.cpp \
	../api/src/service/jcryprorecorder.cpp \
	../api/src/service/jloginservice.cpp \
	../api/src/service/jportservice.cpp \
	../api/src/service/jloginservice2.cpp \
	../api/src/network/jgsinfosocket.cpp \
	../api/src/service/jgsinfoservice.cpp \
	../api/src/global/ssubserver.cpp \
	../api/src/global/jversion.cpp \
    ../api/src/service/jsubserverstartup.cpp

HEADERS += \
    ../api/include/network/jserverbase.h \
    ../api/include/network/jconnectionbase.h \
    network/jgfsconnection.h \
    ../api/include/global/jglobal.h \
    ../api/include/network/jloginsocket.h \
	../api/include/network/jportsocket.h \
	../api/include/network/jsocketbase.h \
	../api/include/service/jcryprorecorder.h \
	../api/include/service/jloginservice.h \
	../api/include/service/jportservice.h \
	../api/include/global/jversion.h \
	../api/include/global/jglobal.h \
	../api/include/global/eportsrv.h \
	../api/include/global/elogin.h \
	../api/include/global/ssubserver.h \
	../api/include/service/jloginservice2.h \
	../api/include/network/jgsinfosocket.h \
	../api/include/service/jgsinfoservice.h \
    ../api/include/service/jsubserverstartup.h
