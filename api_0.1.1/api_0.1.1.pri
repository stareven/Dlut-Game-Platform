INCLUDEPATH += $$PWD/include
QMAKE_RPATHDIR = $$PWD/lib/
LIBS += -L$$PWD/lib -lapi

QT += network
