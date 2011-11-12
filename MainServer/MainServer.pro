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
    database/jabstractlogindb.h \
    database/jtextstreamdatabasefactory.h \
    database/jtextstreamlogindb.h \
    database/jabstractuserinfodb.h \
    database/jtextstreamuserinfodb.h \
    database/jabstractgameinfodb.h \
    database/jabstractserverinfodb.h \
    service/jmainserverinformationmanager.h \
    database/jtextstreamgameinfodb.h \
    database/jtextstreamserverinfodb.h \
    network/jmainserverinformationprocessor.h \
    service/jcommandmanager.h \
    network/jmainservercommandprocessor.h \
    service/jpermissioncontrol.h \
    service/jloginhashcodecreator.h \
    network/jmainserveruserregisterprocessor.h \
    service/juserregister.h \
    network/jmainserversocketstrategy.h
SOURCES += main/main.cpp \
	network/jmainserver.cpp \
    network/jmainserversocket.cpp \
    network/jmainserverloginprocessor.cpp \
    service/jloginverification.cpp \
    database/jabstractdatabasefactory.cpp \
    database/jtextstreamdatabasefactory.cpp \
    database/jtextstreamlogindb.cpp \
    database/jabstractlogindb.cpp \
    database/jabstractuserinfodb.cpp \
    database/jtextstreamuserinfodb.cpp \
    database/jabstractgameinfodb.cpp \
    database/jabstractserverinfodb.cpp \
    service/jmainserverinformationmanager.cpp \
    database/jtextstreamgameinfodb.cpp \
    database/jtextstreamserverinfodb.cpp \
    network/jmainserverinformationprocessor.cpp \
    service/jcommandmanager.cpp \
    network/jmainservercommandprocessor.cpp \
    service/jpermissioncontrol.cpp \
    service/jloginhashcodecreator.cpp \
    network/jmainserveruserregisterprocessor.cpp \
    service/juserregister.cpp \
    network/jmainserversocketstrategy.cpp
