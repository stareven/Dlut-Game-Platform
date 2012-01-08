TEMPLATE  = subdirs
SUBDIRS = api MainClient MainServer test_api SnakeClient SnakeServer \
    CreateDatabase
MainClient.depends = api
MainServer.depends = api
test_api.depends = api
SnakeClient.depends = api
SnakeServer.depends = api
