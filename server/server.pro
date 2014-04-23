TEMPLATE = app

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

LIBS += -L../lib
LIBS += -lboost_system
LIBS += -lnetworklib

DEFINES += PORT=42422

SOURCES += server_main.cpp
