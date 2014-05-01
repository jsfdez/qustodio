include(../common.pri)

TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

LIBS += -L../lib
LIBS += -lcommonlib
LIBS += -lserverlib

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
