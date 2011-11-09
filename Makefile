SUBAPPTARGET = MainClient MainServer GameFileServer1 SnakeServer SnakeClient
define MAKE_SUB_APP_TARGET
$(1)-build-desktop/$(1) : $(1)-build-desktop/Makefile api/lib/libapi.so
	cd $(1)-build-desktop && make
endef
define MAKE_SUB_LIB_TARGET
api/lib/libapi.so : api-build-desktop/Makefile
	cd api-build-desktop && make
endef
define MAKE_APP_MAKEFILE
$(1)-build-desktop/Makefile : $(1)/$(1).pro
	mkdir -p $(1)-build-desktop
	cd $(1)-build-desktop && qmake CONFIG+=debug -o Makefile ../$(1)/$(1).pro
endef
define MAKE_LIB_MAKEFILE
api-build-desktop/Makefile : api/api.pro
	mkdir -p api-build-desktop
	cd api-build-desktop && qmake CONFIG+=debug -o Makefile ../api/api.pro
endef
define MAKE_ALL_TARGET
all : $(1)-build-desktop/$(1)
endef
$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_ALL_TARGET,$(pro))))
$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_SUB_APP_TARGET,$(pro))))
$(foreach pro,$(SUBAPPTARGET),$(eval $(call MAKE_APP_MAKEFILE,$(pro))))
$(eval $(call MAKE_SUB_LIB_TARGET))
$(eval $(call MAKE_LIB_MAKEFILE))
.PHONY : clean-all doc
clean-all :
	find . \( -path '*-build-desktop*' -and -type d \) | xargs rm -rfv
	find . \( -name '*.pro.user' -and -type f \) | xargs rm -rfv
	rm -rfv api/lib
doc :
	cd api && doxygen Doxyfile
