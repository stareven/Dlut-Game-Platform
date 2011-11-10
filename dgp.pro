TEMPLATE  = subdirs
SUBDIRS = api MainClient MainServer SnakeClient SnakeServer test_api
MainClient.depends = api
MainServer.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
test_api.depends = api
