include(../common.pri)
TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

DESTDIR = ../bin
OBJECTS_DIR = .o

INCLUDEPATH += ..

LIBS += -L../lib
LIBS += -lnetworklib
LIBS += -lserverlib
LIBS += -lclientlib

SOURCES += $$files(*.cpp)
