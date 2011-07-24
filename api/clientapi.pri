QT       += network
INCLUDEPATH += $$PWD/clientapi/ \
		$$PWD/include/
HEADERS += \
		$$PWD/clientapi/clientapi_global.h \
		$$PWD/include/service/jcryprorecorder.h \
		$$PWD/include/service/jrequestlogin.h \
		$$PWD/include/service/jrequestport.h \
		$$PWD/include/service/jrequestuserinfo.h
include($$PWD/libglobalapi.pri)
