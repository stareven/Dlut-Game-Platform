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

SOURCES += \
    main/main.cpp \
    ../api/src/network/jserverbase.cpp \
    ../api/src/network/jconnectionbase.cpp \
    network/jgfsconnection.cpp \
	../api/src/network/jrequestloginsocket.cpp \
	../api/src/network/jrequestportsocket.cpp \
	../api/src/network/jsocketbase.cpp \
	../api/src/service/jcryprorecorder.cpp \
	../api/src/service/jrequestport.cpp \
	../api/src/service/jrequestlogin.cpp \
	../api/src/network/jsendgsinfosocket.cpp \
	../api/src/service/jsendgsinfo.cpp \
	../api/src/global/ssubserver.cpp \
	../api/src/global/jversion.cpp \
    ../api/src/service/jsubserverstartup.cpp \
    service/jgamefilemanager.cpp \
    ../api/src/service/jrequestbase.cpp \
    ../api/src/service/jplhrequestbase.cpp \
    ../api/src/network/jplhsocketbase.cpp \
    network/jgfsserver.cpp \
    ../api/src/global/shost.cpp

HEADERS += \
    ../api/include/network/jserverbase.h \
    ../api/include/network/jconnectionbase.h \
    network/jgfsconnection.h \
    ../api/include/global/jglobal.h \
    ../api/include/network/jrequestloginsocket.h \
	../api/include/network/jrequestportsocket.h \
	../api/include/network/jsocketbase.h \
	../api/include/service/jcryprorecorder.h \
	../api/include/service/jrequestport.h \
	../api/include/global/jversion.h \
	../api/include/global/jglobal.h \
	../api/include/global/eportsrv.h \
	../api/include/global/elogin.h \
	../api/include/global/ssubserver.h \
	../api/include/service/jrequestlogin.h \
	../api/include/network/jsendgsinfosocket.h \
	../api/include/service/jsendgsinfo.h \
    ../api/include/service/jsubserverstartup.h \
    service/jgamefilemanager.h \
    ../api/include/global/magicnumber.h \
    ../api/include/service/jrequestbase.h \
    ../api/include/service/jplhrequestbase.h \
    ../api/include/network/jplhsocketbase.h \
    network/jgfsserver.h
