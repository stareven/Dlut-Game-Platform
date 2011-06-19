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
    network/jgameinfosocket.cpp \
    service/jgameinfoservice.cpp \
    service/jportservice.cpp \
    ../api/src/global/jversion.cpp \
    ../api/src/global/ssubserver.cpp \
    service/jdownloadrun.cpp \
    ../api/src/network/jsocketbase.cpp \
    ../api/src/service/jcryprorecorder.cpp \
    ../api/src/service/jloginservice2.cpp \
    ../api/src/service/jloginservice.cpp \
    ../api/src/network/jloginsocket.cpp \
    ../api/src/network/jportsocket.cpp
HEADERS += gui/mainwindow.h \
    gui/dlglogin/jcomboselectserver.h \
    gui/dlglogin/jdlglogin.h \
    gui/dlglogin/jdlgnewserver.h \
    gui/dlglogin/shallserver.h \
    gui/dlglogin/settings/jrememberpassword.h \
    gui/dlglogin/settings/jsettinglogin.h \
    ../api/include/global/elogin.h \
    ../api/include/global/jglobal.h \
    ../api/include/global/jversion.h \
    ../api/include/global/jelapsedtimer.h \
    ../api/include/global/ssubserver.h \
    ../api/include/network/jsocketbase.h \
    network/jgameinfosocket.h \
    service/jgameinfoservice.h \
    ../api/include/global/eportsrv.h \
    service/jportservice.h \
    service/jdownloadrun.h \
    ../api/include/service/jcryprorecorder.h \
    ../api/include/service/jloginservice2.h \
    ../api/include/service/jloginservice.h \
    ../api/include/network/jloginsocket.h \
    ../api/include/network/jportsocket.h
FORMS += gui/mainwindow.ui \
    gui/dlglogin/jdlglogin.ui \
    gui/dlglogin/jdlgnewserver.ui
