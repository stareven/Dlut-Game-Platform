SUBAPPTARGET = MainClient MainServer GameFileServer1 SnakeServer SnakeClient
SUBLIBTARGET = global client server subserver
define MAKE_SUB_APP_TARGET
$(1)-build-desktop/$(1) : $(1)-build-desktop/Makefile
	cd $(1)-build-desktop && make
endef
define MAKE_SUB_LIB_TARGET
api/lib/lib$(1)api.so : api/$(1)api-build-desktop/Makefile
	cd api/$(1)-build-desktop && make
endef
define MAKE_APP_MAKEFILE
$(1)-build-desktop/Makefile : $(1)/$(1).pro
	qmake CONFIG+=debug -o $(1)-build-desktop/Makefile $(1)/$(1).pro
endef
define MAKE_LIB_MAKEFILE
api/$(1)api-build-desktop/Makefile : api/$(1)api/$(1)api.pro
	qmake CONFIG+=debug -o api/$(1)-build-desktop/Makefile api/$(1)api/$(1)api.pro
endef
define MAKE_ALL_TARGET
all : $(1)-build-desktop/$(1)
endef
$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_ALL_TARGET,$(pro))))
MainClient-build-desktop/MainClient : api/lib/libclientapi.so
MainServer-build-desktop/MainServer : api/lib/libserverapi.so
GameFileServer1-build-desktop/GameFileServer1 : api/lib/libsubserverapi.so
SnakeServer-build-desktop/SnakeServer : api/lib/libsubserverapi.so
SnakeClient-build-desktop/SnakeClient : api/lib/libclientapi.so
api/lib/libglobalapi.so : 
api/lib/libclientapi.so : api/lib/libglobalapi.so
api/lib/libserverapi.so : api/lib/libglobalapi.so
api/lib/libsubserverapi.so : api/lib/libserverapi.so api/lib/libclientapi.so

$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_SUB_APP_TARGET,$(pro))))
$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_APP_MAKEFILE,$(pro))))
$(foreach pro,$(SUBLIBTARGET),$(eval $(call MAKE_SUB_LIB_TARGET,$(pro))))
$(foreach pro,$(SUBLIBTARGET),$(eval $(call MAKE_LIB_MAKEFILE,$(pro))))
clean-all :
	find . \( -path '*-build-desktop*' -and -type d \) | xargs rm -rfv
	find . \( -name '*.pro.user' -and -type f \) | xargs rm -rfv
	rm -rfv api/lib
