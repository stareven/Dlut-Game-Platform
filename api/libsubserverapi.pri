include(subserverapi.pri)
LIBS += -L$$PWD/libsubserverapi -lsubserverapi
QMAKE_RPATHDIR += $$PWD/libsubserverapi/
