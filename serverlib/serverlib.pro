TEMPLATE = lib

QT =
CONFIG += staticlib

OBJECTS_DIR = .o
DESTDIR = ../lib

INCLUDEPATH += ..
INCLUDEPATH += ../3rdParty/rapidjson/include

win32 {
    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$(BOOST_PATH)/stage/lib
    DEFINES += _WIN32_WINNT=0x0600
}

LIBS += -L../lib
LIBS += -lnetworklib

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
