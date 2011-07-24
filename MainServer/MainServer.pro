# -------------------------------------------------
# Project created by QtCreator 2011-03-06T12:57:13
# -------------------------------------------------
QT -= gui
QT += network
TARGET = MainServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
HEADERS += \
    network/jservertype.h \
    service/jloginverification.h \
    database/jabslogindb.h \
    service/jloginhash.h \
    service/juserisonline.h \
    network/jconnectionfactory.h \
    network/jloginconnection.h \
    network/jgameinfoconnection.h \
    service/jportmanager.h \
    network/jportconnection.h \
    network/jsubserverconnection.h \
    service/jsubserversrv.h \
	network/jplhconnectionbase.h \
    database/jsubserverdb.h \
    database/jgameinfodb.h \
    network/juserinfoconnection.h \
	database/juserinfodb.h
SOURCES += main/main.cpp \
    network/jservertype.cpp \
    service/jloginverification.cpp \
    database/jabslogindb.cpp \
    service/jloginhash.cpp \
	service/juserisonline.cpp \
    network/jconnectionfactory.cpp \
    network/jloginconnection.cpp \
    network/jgameinfoconnection.cpp \
    service/jportmanager.cpp \
    network/jportconnection.cpp \
    network/jsubserverconnection.cpp \
    service/jsubserversrv.cpp \
	network/jplhconnectionbase.cpp \
    database/jsubserverdb.cpp \
    database/jgameinfodb.cpp \
    network/juserinfoconnection.cpp \
	database/juserinfodb.cpp
include(../api/libserverapi.pri)
