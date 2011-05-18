# -------------------------------------------------
# Project created by QtCreator 2011-03-06T12:57:13
# -------------------------------------------------
QT -= gui
QT += network
TARGET = MainServer
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../include
SOURCES += main/main.cpp \
    network/jserverbase.cpp \
    network/jconnectionbase.cpp \
    service/jloginverification.cpp \
    service/juserlogincrypro.cpp \
    database/jabslogindb.cpp \
    service/jloginhash.cpp \
    service/juserisonline.cpp \
    service/jgameinfosrv.cpp \
    network/jconnectionfactory.cpp \
    network/jloginconnection.cpp \
    network/jgameinfoconnection.cpp \
    service/jportservice.cpp \
    network/jportconnection.cpp \
    network/jgameserverconnection.cpp \
    ../include/sgame.cpp \
    network/jsubserverconnection.cpp
HEADERS += network/jserverbase.h \
    network/jconnectionbase.h \
    service/jloginverification.h \
    service/juserlogincrypro.h \
    database/jabslogindb.h \
    service/jloginhash.h \
    service/juserisonline.h \
    ../include/elogin.h \
    ../include/sgame.h \
    ../include/jglobal.h \
    ../include/jversion.h \
    ../include/egameinfo.h \
    service/jgameinfosrv.h \
    network/jconnectionfactory.h \
    network/jloginconnection.h \
    network/jgameinfoconnection.h \
    service/jportservice.h \
    network/jportconnection.h \
    ../include/eportsrv.h \
    network/jgameserverconnection.h \
    ../include/egameserver.h \
    network/jsubserverconnection.h \
    ../include/ssubserver.h
