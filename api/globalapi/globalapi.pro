#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------
QT -= gui
TARGET = globalapi
TEMPLATE = lib

include(../globalapi.pri)

DEFINES += GLOBALAPI_LIBRARY

SOURCES += \
    ../src/global/ssubserver.cpp \
	../src/global/jversion.cpp \
	../src/global/userinfo.cpp \
	../src/global/shost.cpp
HEADERS += \
	globalapi_global.h \
	../include/global/elogin.h \
	../include/global/jglobal.h \
	../include/global/jversion.h \
	../include/global/eportsrv.h \
	../include/global/ssubserver.h \
	../include/global/magicnumber.h \
	../include/global/userinfo.h \
	../include/global/shost.h
DESTDIR = ../lib
