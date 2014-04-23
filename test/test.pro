TEMPLATE = app

QT =

DESTDIR = ../bin
OBJECTS_DIR = .o

INCLUDEPATH += ..

LIBS += -lboost_unit_test_framework
LIBS += -L../lib
LIBS += -lboost_system
LIBS += -lnetworklib

SOURCES += test.cpp
