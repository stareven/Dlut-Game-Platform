# -------------------------------------------------
# Project created by QtCreator 2011-03-13T18:59:56
# -------------------------------------------------
TARGET = MainClient
TEMPLATE = app
SOURCES += main/main.cpp \
    gui/mainwindow.cpp \
    gui/dlglogin/jcomboselectserver.cpp \
    gui/dlglogin/jdlglogin.cpp \
    gui/dlglogin/jdlgnewserver.cpp \
    gui/dlglogin/shallserver.cpp \
    gui/dlglogin/settings/jrememberpassword.cpp \
    gui/dlglogin/settings/jsettinglogin.cpp \
	service/jdownloadrun.cpp \
    gui/jdlgselectserver.cpp
HEADERS += gui/mainwindow.h \
    gui/dlglogin/jcomboselectserver.h \
    gui/dlglogin/jdlglogin.h \
    gui/dlglogin/jdlgnewserver.h \
    gui/dlglogin/shallserver.h \
    gui/dlglogin/settings/jrememberpassword.h \
    gui/dlglogin/settings/jsettinglogin.h \
    service/jdownloadrun.h \
    gui/jdlgselectserver.h
FORMS += gui/mainwindow.ui \
    gui/dlglogin/jdlglogin.ui \
    gui/dlglogin/jdlgnewserver.ui \
    gui/jdlgselectserver.ui
include(../api/api.pri)
QMAKE_RPATHDIR = ../api/lib
RESOURCES += \
    sources.qrc
