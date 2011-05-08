######################################################################
# Automatically generated by qmake (2.01a) ?? 4? 28 15:40:21 2011
######################################################################

TEMPLATE = app
QT       += core
QT       += network

QT       -= gui

TARGET = SampleServer
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH += ../include

# Input
HEADERS += main/jargumentanalyse.h \
           network/jloginsocket.h \
           network/jportsocket.h \
           network/jsocketbase.h \
           service/jcryprorecorder.h \
           service/jloginservice.h \
           service/jportservice.h \
    ../include/sgame.h \
    ../include/jversion.h \
    ../include/jglobal.h \
    ../include/eportsrv.h \
    ../include/elogin.h \
    service/jloginservice2.h
SOURCES += main/jargumentanalyse.cpp \
           main/main.cpp \
           network/jloginsocket.cpp \
           network/jportsocket.cpp \
           network/jsocketbase.cpp \
           service/jcryprorecorder.cpp \
           service/jloginservice.cpp \
           service/jportservice.cpp \
    service/jloginservice2.cpp
