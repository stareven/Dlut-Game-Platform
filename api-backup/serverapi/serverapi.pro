#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------
QT       -= gui
TARGET = serverapi
TEMPLATE = lib

include(../serverapi.pri)

DEFINES += SERVERAPI_LIBRARY

SOURCES += \
    ../src/network/jserverbase.cpp \
    ../src/network/jconnectionbase.cpp
HEADERS += \
	serverapi_global.h \
	../include/network/jserverbase.h \
	../include/network/jconnectionbase.h
DESTDIR = ../lib
