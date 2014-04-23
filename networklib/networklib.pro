TEMPLATE = lib

QT =

OBJECTS_DIR = .o
DESTDIR = ../lib
INCLUDEPATH += .

win32 {
	INCLUDEPATH += $$(BOOST_PATH)
}

!win32 {
	QMAKE_CXXFLAGS += -std=c++11
}

HEADERS += server.h
SOURCES += server.cpp
