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
    network/jrequestgameinfosocket.cpp \
	service/jrequestgameinfo.cpp \
	service/jdownloadrun.cpp \
    ../api/src/global/jversion.cpp \
    ../api/src/global/ssubserver.cpp \
    ../api/src/network/jsocketbase.cpp \
    ../api/src/service/jcryprorecorder.cpp \
    ../api/src/service/jrequestlogin.cpp \
	../api/src/service/jrequestport.cpp \
    ../api/src/network/jrequestloginsocket.cpp \
    ../api/src/network/jrequestportsocket.cpp \
    network/jdownloadgamefilesocket.cpp \
    ../api/src/service/jrequestbase.cpp \
    ../api/src/service/jplhrequestbase.cpp \
    ../api/src/network/jplhsocketbase.cpp \
    ../api/src/network/jrequestuserinfosocket.cpp \
    ../api/src/global/userinfo.cpp \
    ../api/src/service/jrequestuserinfo.cpp
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
    network/jrequestgameinfosocket.h \
    service/jrequestgameinfo.h \
	../api/include/global/eportsrv.h \
    service/jdownloadrun.h \
    ../api/include/service/jcryprorecorder.h \
    ../api/include/service/jrequestlogin.h \
	../api/include/service/jrequestport.h \
    ../api/include/network/jrequestloginsocket.h \
    ../api/include/network/jrequestportsocket.h \
    network/jdownloadgamefilesocket.h \
    ../api/include/global/magicnumber.h \
    ../api/include/service/jrequestbase.h \
    ../api/include/service/jplhrequestbase.h \
    ../api/include/network/jplhsocketbase.h \
    ../api/include/network/jrequestuserinfosocket.h \
    ../api/include/global/userinfo.h \
    ../api/include/service/jrequestuserinfo.h
FORMS += gui/mainwindow.ui \
    gui/dlglogin/jdlglogin.ui \
    gui/dlglogin/jdlgnewserver.ui
