include(clientapi.pri)
LIBS += -L$$PWD/libclientapi -lclientapi
QMAKE_RPATHDIR += $$PWD/libclientapi/
