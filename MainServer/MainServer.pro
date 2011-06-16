# -------------------------------------------------
# Project created by QtCreator 2011-03-06T12:57:13
# -------------------------------------------------
QT -= gui
QT += network
TARGET = MainServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../api/include
HEADERS += network/jserverbase.h \
    network/jconnectionbase.h \
    service/jloginverification.h \
    service/juserlogincrypro.h \
    database/jabslogindb.h \
    service/jloginhash.h \
	service/juserisonline.h \
    network/jconnectionfactory.h \
    network/jloginconnection.h \
    network/jgameinfoconnection.h \
    service/jportservice.h \
    network/jportconnection.h \
    network/jsubserverconnection.h \
    service/jsubserversrv.h \
	network/jplhconnectionbase.h \
	../api/include/global/elogin.h \
	../api/include/global/jglobal.h \
	../api/include/global/jversion.h \
	../api/include/global/eportsrv.h \
	../api/include/global/ssubserver.h \
    database/jsubserverdb.h \
    database/jgameinfodb.h
SOURCES += main/main.cpp \
    network/jserverbase.cpp \
    network/jconnectionbase.cpp \
    service/jloginverification.cpp \
    service/juserlogincrypro.cpp \
    database/jabslogindb.cpp \
    service/jloginhash.cpp \
	service/juserisonline.cpp \
    network/jconnectionfactory.cpp \
    network/jloginconnection.cpp \
    network/jgameinfoconnection.cpp \
    service/jportservice.cpp \
    network/jportconnection.cpp \
	../api/src/global/ssubserver.cpp \
    network/jsubserverconnection.cpp \
    service/jsubserversrv.cpp \
	network/jplhconnectionbase.cpp \
    ../api/src/global/jversion.cpp \
    database/jsubserverdb.cpp \
    database/jgameinfodb.cpp
