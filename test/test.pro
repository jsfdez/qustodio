TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

DESTDIR = ../bin
OBJECTS_DIR = .o

INCLUDEPATH += ..

win32 {
    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$(BOOST_PATH)/stage/lib
    DEFINES += _WIN32_WINNT=0x0600
}

LIBS += -L../lib
LIBS += -lnetworklib
LIBS += -lserverlib
LIBS += -lclientlib

SOURCES += $$files(*.cpp)
