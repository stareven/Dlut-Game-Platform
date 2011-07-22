include(globalapi.pri)
LIBS += -L$$PWD/libglobalapi -lglobalapi
QMAKE_RPATHDIR += $$PWD/libglobalapi/
