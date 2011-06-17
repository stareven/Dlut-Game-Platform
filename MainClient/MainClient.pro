# -------------------------------------------------
# Project created by QtCreator 2011-03-13T18:59:56
# -------------------------------------------------
QT += network
TARGET = MainClient
TEMPLATE = app
INCLUDEPATH += ../api/include
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
    ../api/src/global/jversion.cpp \
    ../api/src/global/ssubserver.cpp \
    service/jdownloadrun.cpp
HEADERS += gui/mainwindow.h \
    gui/dlglogin/jcomboselectserver.h \
    gui/dlglogin/jdlglogin.h \
    gui/dlglogin/jdlgnewserver.h \
    gui/dlglogin/shallserver.h \
    gui/dlglogin/settings/jrememberpassword.h \
    gui/dlglogin/settings/jsettinglogin.h \
    network/jloginsocket.h \
    service/jloginservice.h \
    ../api/include/global/elogin.h \
    ../api/include/global/jglobal.h \
    ../api/include/global/jversion.h \
    ../api/include/global/jelapsedtimer.h \
    ../api/include/global/ssubserver.h \
    network/jgameinfosocket.h \
    service/jcryprorecorder.h \
    network/jsocketbase.h \
    service/jgameinfoservice.h \
    network/jportsocket.h \
    ../api/include/global/eportsrv.h \
    service/jportservice.h \
    service/jdownloadrun.h
FORMS += gui/mainwindow.ui \
    gui/dlglogin/jdlglogin.ui \
    gui/dlglogin/jdlgnewserver.ui
