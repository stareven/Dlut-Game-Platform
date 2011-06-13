# -------------------------------------------------
# Project created by QtCreator 2011-03-13T18:59:56
# -------------------------------------------------
QT += network
TARGET = MainClient
TEMPLATE = app
INCLUDEPATH += ../include
SOURCES += main/main.cpp \
    gui/mainwindow.cpp \
    gui/dlglogin/jcomboselectserver.cpp \
    gui/dlglogin/jdlglogin.cpp \
    gui/dlglogin/jdlgnewserver.cpp \
    gui/dlglogin/shallserver.cpp \
    gui/dlglogin/settings/jrememberpassword.cpp \
    gui/dlglogin/settings/jsettinglogin.cpp \
    network/jloginsocket.cpp \
    service/jloginservice.cpp \
    network/jgameinfosocket.cpp \
    service/jcryprorecorder.cpp \
    network/jsocketbase.cpp \
    service/jgameinfoservice.cpp \
    network/jportsocket.cpp \
    service/jportservice.cpp \
    ../include/jversion.cpp \
    ../include/ssubserver.cpp
HEADERS += gui/mainwindow.h \
    gui/dlglogin/jcomboselectserver.h \
    gui/dlglogin/jdlglogin.h \
    gui/dlglogin/jdlgnewserver.h \
    gui/dlglogin/shallserver.h \
    gui/dlglogin/settings/jrememberpassword.h \
    gui/dlglogin/settings/jsettinglogin.h \
    network/jloginsocket.h \
    service/jloginservice.h \
    ../include/elogin.h \
    ../include/jglobal.h \
    ../include/jversion.h \
    ../include/jelapsedtimer.h \
    ../include/ssubserver.h \
    network/jgameinfosocket.h \
    service/jcryprorecorder.h \
    network/jsocketbase.h \
    service/jgameinfoservice.h \
    network/jportsocket.h \
    ../include/eportsrv.h \
    service/jportservice.h
FORMS += gui/mainwindow.ui \
    gui/dlglogin/jdlglogin.ui \
    gui/dlglogin/jdlgnewserver.ui
DEFINES += DGP_MAIN_CLIENT
