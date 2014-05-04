include(../common.pri)

TEMPLATE = lib
QT =
win32 {
    CONFIG += staticlib
}
CONFIG -= qt
OBJECTS_DIR = .o
DESTDIR = ../lib
INCLUDEPATH += ..
INCLUDEPATH += ../3rdParty/rapidjson/include

LIBS += -L../lib
LIBS += -lcommonlib

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
