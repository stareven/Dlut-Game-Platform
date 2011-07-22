include(serverapi.pri)
LIBS += -L$$PWD/libserverapi -lserverapi
QMAKE_RPATHDIR += $$PWD/libserverapi/
