include(../common.pri)

TEMPLATE = lib
QT =
CONFIG += staticlib
CONFIG -= qt
OBJECTS_DIR = .o
DESTDIR = ../lib
INCLUDEPATH += ..
INCLUDEPATH += ../3rdParty/rapidjson/include

LIBS += -L../lib
LIBS += -lnetworklib

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
