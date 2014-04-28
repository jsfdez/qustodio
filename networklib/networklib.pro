TEMPLATE = lib

QT =
CONFIG += staticlib

OBJECTS_DIR = .o
DESTDIR = ../lib
INCLUDEPATH += .

win32 {
    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$(BOOST_PATH)/stage/lib
    DEFINES += _WIN32_WINNT=0x0600
}

!win32 {
    QMAKE_CXXFLAGS += -std=c++11
}

HEADERS += server.h
SOURCES += server.cpp
