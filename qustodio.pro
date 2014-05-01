include(common.pri)

TEMPLATE = subdirs

CONFIG -= qt

QT =

# Directories
SUBDIRS += commonlib
SUBDIRS += serverlib
SUBDIRS += clientlib
SUBDIRS += server
SUBDIRS += client
SUBDIRS += test

serverlib.depends = commonlib
clientlib.depends = commonlib
server.depends = serverlib
client.depends = clientlib
test.depends += serverlib
test.depends += clientlib

OTHER_FILES += docs/sample.log
