INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/../../dgp-build-desktop/api/ -lapi
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../api
CONFIG += use_prl
QT += network
