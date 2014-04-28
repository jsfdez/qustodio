TEMPLATE = subdirs

CONFIG -= qt

QT =

win32 {
    DEFINES += _WIN32_WINNT=0x0600
}

# Directories
SUBDIRS += networklib
SUBDIRS += serverlib
SUBDIRS += clientlib
SUBDIRS += server
SUBDIRS += client
SUBDIRS += test
