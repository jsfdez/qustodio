include(../common.pri)

TEMPLATE = app

CONFIG += console
CONFIG -= qt

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

win32 {
    QMAKE_CXXFLAGS += -EHsc
}

LIBS += -L../lib
LIBS += -lcommonlib
LIBS += -lclientlib


HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
