#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------

QT       -= gui

TARGET = globalapi
TEMPLATE = lib

include(../globalapi.pri)

DEFINES += SERVERAPI_LIBRARY

SOURCES += \
    ../src/global/ssubserver.cpp \
	../src/global/jversion.cpp \
	../src/global/userinfo.cpp \
	../src/global/shost.cpp
