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

HEADERS += \
    service/jloginverification.h \
    database/jabslogindb.h \
    service/jloginhash.h \
	service/juserisonline.h \
	service/jportmanager.h \
	service/jsubserversrv.h \
    database/jsubserverdb.h \
	database/jgameinfodb.h \
	database/juserinfodb.h \
    network/jmainserver.h
SOURCES += main/main.cpp \
    service/jloginverification.cpp \
    database/jabslogindb.cpp \
    service/jloginhash.cpp \
	service/juserisonline.cpp \
	service/jportmanager.cpp \
	service/jsubserversrv.cpp \
    database/jsubserverdb.cpp \
	database/jgameinfodb.cpp \
	database/juserinfodb.cpp \
	network/jmainserver.cpp
