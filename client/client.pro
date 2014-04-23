TEMPLATE = app

CONFIG = console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

!win32 {
	LIBS += L../lib
}

SOURCES += client_main.cpp
