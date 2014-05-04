include(../common.pri)

TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

DESTDIR = ../bin
OBJECTS_DIR = .o

INCLUDEPATH += ..

LIBS += -L../lib
LIBS += -lcommonlib
LIBS += -lserverlib
LIBS += -lclientlib
!win32 {
    LIBS += -lboost_unit_test_framework
    LIBS += -lpthread
}

SOURCES += $$files(*.cpp)
