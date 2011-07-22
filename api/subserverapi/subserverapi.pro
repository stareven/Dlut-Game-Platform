#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = subserverapi
TEMPLATE = lib

include(../subserverapi.pri)

DEFINES += SUBSERVERAPI_LIBRARY

SOURCES += \
    ../src/service/jsubserverstartup.cpp \
    ../src/service/jsendgsinfo.cpp \
    ../src/network/jsendgsinfosocket.cpp
