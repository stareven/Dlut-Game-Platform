#-------------------------------------------------
#
# Project created by QtCreator 2011-07-22T10:40:24
#
#-------------------------------------------------
QT -= gui
TARGET = clientapi
TEMPLATE = lib

include(../clientapi.pri)

DEFINES += CLIENTAPI_LIBRARY

SOURCES += \
		../src/network/jsocketbase.cpp \
		../src/service/jloginhashcoderecorder.cpp \
		../src/service/jrequestlogin.cpp \
		../src/service/jrequestport.cpp \
		../src/network/jrequestloginsocket.cpp \
		../src/network/jrequestportsocket.cpp \
		../src/service/jrequestbase.cpp \
		../src/service/jlhcrequestbase.cpp \
		../src/network/jlhcsocketbase.cpp \
		../src/network/jrequestuserinfosocket.cpp \
		../src/service/jrequestuserinfo.cpp
HEADERS += \
		../include/network/jrequestloginsocket.h \
		../include/network/jrequestportsocket.h \
		../include/network/jrequestuserinfosocket.h \
		../include/service/jrequestbase.h \
		../include/service/jlhcrequestbase.h
DESTDIR = ../lib
