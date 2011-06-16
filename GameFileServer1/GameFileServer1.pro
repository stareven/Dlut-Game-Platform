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

INCLUDEPATH += ../include

SOURCES += main/main.cpp \
    network/jserverbase.cpp \
    network/jconnectionbase.cpp \
    network/jgfsconnection.cpp

HEADERS += \
    network/jserverbase.h \
    network/jconnectionbase.h \
    network/jgfsconnection.h \
    ../include/jglobal.h
