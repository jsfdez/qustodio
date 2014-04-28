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

#LIBS += -lboost_system
LIBS += -lnetworklib

DEFINES += PORT=42422

SOURCES += server_main.cpp
