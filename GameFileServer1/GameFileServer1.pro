#-------------------------------------------------
#
# Project created by QtCreator 2011-05-12T17:24:46
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = GameFileServer1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main/main.cpp \
    network/jgfsconnection.cpp \
    service/jgamefilemanager.cpp \
	network/jgfsserver.cpp

HEADERS += \
    network/jgfsconnection.h \
    service/jgamefilemanager.h \
    network/jgfsserver.h
include(../api/libserverapi.pri)
include(../api/libsubserverapi.pri)
