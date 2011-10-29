# -------------------------------------------------
# Project created by QtCreator 2011-03-06T12:57:13
# -------------------------------------------------
QT -= gui
QT += network
TARGET = MainServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

include(../api/api.pri)
QMAKE_RPATHDIR = ../api/lib

HEADERS += \
    network/jmainserver.h \
    network/jmainserversocket.h \
    network/jmainserverloginprocessor.h \
    service/jloginverification.h \
    database/jabstractdatabasefactory.h \
    database/jabslogindb.h \
    database/jtextstreamdatabasefactory.h \
    database/jtextstreamlogindb.h
SOURCES += main/main.cpp \
	network/jmainserver.cpp \
    network/jmainserversocket.cpp \
    network/jmainserverloginprocessor.cpp \
    service/jloginverification.cpp \
    database/jabstractdatabasefactory.cpp \
    database/jtextstreamdatabasefactory.cpp \
    database/jtextstreamlogindb.cpp \
    database/jabslogindb.cpp
