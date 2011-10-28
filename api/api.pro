######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 20 18:37:45 2011
######################################################################

QT += network
TEMPLATE = lib
TARGET = api
VERSION = 0.1.1
DESTDIR = $$PWD/lib/

# Input
HEADERS += src/network/jnetworkdataprocessorbase.h src/network/jsocketbase.h \
    src/global/jglobal.h \
    src/network/jclientsocketbase.h \
    src/network/jserversocketbase.h \
    src/network/jclientnetworkdataprocessorbase.h \
    src/network/jclientloginprocessor.h \
    src/request/jrequestlogin.h \
    src/request/jrequestbase.h \
    src/global/elogin.h \
    src/global/shost.h \
    src/network/jinformation.h \
    src/network/jclientdownloadinformationprocessor.h \
    src/network/jinformationmanager.h \
    src/global/jserializabledata.h \
    src/request/jrequestuserinfo.h \
    src/global/juserinfo.h \
    src/request/jinformationrequestbase.h \
    src/global/jgameinfo.h \
    src/request/jrequestgameinfo.h \
    src/global/jversion.h \
    src/global/jserverinfo.h \
    src/request/jrequestserverinfo.h \
    src/network/jclientuploadinformationprocessor.h \
    src/request/jinformationsendbase.h \
    src/request/juploadgameinfo.h \
    src/request/juploadserverinfo.h \
    src/network/jserverbase.h
SOURCES += src/network/jsocketbase.cpp \
    src/network/jclientsocketbase.cpp \
    src/network/jserversocketbase.cpp \
    src/network/jclientnetworkdataprocessorbase.cpp \
    src/network/jclientloginprocessor.cpp \
    src/request/jrequestlogin.cpp \
    src/request/jrequestbase.cpp \
    src/global/shost.cpp \
    src/network/jinformation.cpp \
    src/network/jclientdownloadinformationprocessor.cpp \
    src/network/jinformationmanager.cpp \
    src/request/jrequestuserinfo.cpp \
    src/global/juserinfo.cpp \
    src/request/jinformationrequestbase.cpp \
    src/global/jgameinfo.cpp \
    src/request/jrequestgameinfo.cpp \
    src/global/jversion.cpp \
    src/global/jserverinfo.cpp \
    src/request/jrequestserverinfo.cpp \
    src/network/jclientuploadinformationprocessor.cpp \
    src/request/jinformationsendbase.cpp \
    src/request/juploadgameinfo.cpp \
    src/request/juploadserverinfo.cpp \
    src/global/jserializabledata.cpp \
    src/network/jserverbase.cpp

OTHER_FILES += \
    ../doc/rebuild-network.txt
