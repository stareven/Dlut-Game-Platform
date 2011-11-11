TEMPLATE  = subdirs
SUBDIRS = api MainClient MainServer test_api
MainClient.depends = api
MainServer.depends = api
test_api.depends = api
