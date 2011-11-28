INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib -lapi
unix:!mac:QMAKE_LFLAGS += -Wl,--rpath=../api
CONFIG += use_prl
QT += network
