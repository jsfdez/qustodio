include(../common.pri)

TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

LIBS += -L../lib

LIBS += -lnetworklib
LIBS += -lserverlib

DEFINES += PORT=42422

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
