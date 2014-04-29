TEMPLATE = app

CONFIG -= qt
CONFIG += console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

INCLUDEPATH += ..

LIBS += -L../lib

win32 {
    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$(BOOST_PATH)/stage/lib
    DEFINES += _WIN32_WINNT=0x0600
}

LIBS += -lnetworklib
LIBS += -lserverlib

DEFINES += PORT=42422

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
