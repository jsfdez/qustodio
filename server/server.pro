TEMPLATE = app

CONFIG = console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

win32 {
	INCLUDEPATH += $$(BOOST_PATH)
}

LIBS += -L../lib
LIBS += -lboost_system
LIBS += -lnetworklib

DEFINES += PORT=42422

SOURCES += server_main.cpp
