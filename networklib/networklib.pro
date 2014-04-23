TEMPLATE = lib

QT =

OBJECTS_DIR = .o
DESTDIR = ../lib
INCLUDEPATH += .

QMAKE_CXXFLAGS += -std=c++11

HEADERS += server.h
SOURCES += server.cpp
