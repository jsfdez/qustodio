include(common.pri)

TEMPLATE = subdirs

CONFIG -= qt

QT =

# Directories
SUBDIRS += networklib
SUBDIRS += serverlib
SUBDIRS += clientlib
SUBDIRS += server
SUBDIRS += client
SUBDIRS += test

serverlib.depends = networklib
clientlib.depends = networklib
server.depends = serverlib
client.depends = clientlib
test.depends += serverlib
test.depends += clientlib

OTHER_FILES += docs/sample.log
