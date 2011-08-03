all : MainClient-build-desktop/MainClient MainServer-build-desktop/MainServer GameFileServer1-build-desktop/GameFileServer1 SnakeServer-build-desktop/SnakeServer SnakeClient-build-desktop/SnakeClient
MainClient-build-desktop/MainClient : MainClient-build-desktop/Makefile api/lib/libclientapi.so
	make -C MainClient-build-desktop
MainServer-build-desktop/MainServer : MainServer-build-desktop/Makefile api/lib/libserverapi.so
	make -C MainServer-build-desktop
GameFileServer1-build-desktop/GameFileServer1 : GameFileServer1-build-desktop/Makefile api/lib/libsubserverapi.so
	make -C GameFileServer1-build-desktop
SnakeServer-build-desktop/SnakeServer : SnakeServer-build-desktop/Makefile api/lib/libsubserverapi.so
	make -C SnakeServer-build-desktop
SnakeClient-build-desktop/SnakeClient : SnakeClient-build-desktop/Makefile api/lib/libclientapi.so
	make -C SnakeClient-build-desktop
api/lib/libglobalapi.so : api/globalapi-build-desktop/Makefile
	make -C api/globalapi-build-desktop
api/lib/libclientapi.so : api/clientapi-build-desktop/Makefile api/lib/libglobalapi.so
	make -C api/clientapi-build-desktop
api/lib/libserverapi.so : api/serverapi-build-desktop/Makefile api/lib/libglobalapi.so
	make -C api/serverapi-build-desktop
api/lib/libsubserverapi.so : api/subserverapi-build-desktop/Makefile api/lib/libserverapi.so api/lib/libclientapi.so
	make -C api/subserverapi-build-desktop
SnakeClient-build-desktop/Makefile  :  SnakeClient/SnakeClient.pro
	 qmake CONFIG+=debug -o SnakeClient-build-desktop/Makefile SnakeClient/SnakeClient.pro
SnakeServer-build-desktop/Makefile  :  SnakeServer/SnakeServer.pro
	 qmake CONFIG+=debug -o SnakeServer-build-desktop/Makefile SnakeServer/SnakeServer.pro
GameFileServer1-build-desktop/Makefile  :  GameFileServer1/GameFileServer1.pro
	 qmake CONFIG+=debug -o GameFileServer1-build-desktop/Makefile GameFileServer1/GameFileServer1.pro
api/subserverapi-build-desktop/Makefile  :  api/subserverapi/subserverapi.pro
	 qmake CONFIG+=debug -o api/subserverapi-build-desktop/Makefile api/subserverapi/subserverapi.pro
api/globalapi-build-desktop/Makefile  :  api/globalapi/globalapi.pro
	 qmake CONFIG+=debug -o api/globalapi-build-desktop/Makefile api/globalapi/globalapi.pro
api/clientapi-build-desktop/Makefile  :  api/clientapi/clientapi.pro
	 qmake CONFIG+=debug -o api/clientapi-build-desktop/Makefile api/clientapi/clientapi.pro
api/serverapi-build-desktop/Makefile  :  api/serverapi/serverapi.pro
	 qmake CONFIG+=debug -o api/serverapi-build-desktop/Makefile api/serverapi/serverapi.pro
MainClient-build-desktop/Makefile  :  MainClient/MainClient.pro
	 qmake CONFIG+=debug -o MainClient-build-desktop/Makefile MainClient/MainClient.pro
MainServer-build-desktop/Makefile  :  MainServer/MainServer.pro
	 qmake CONFIG+=debug -o MainServer-build-desktop/Makefile MainServer/MainServer.pro
