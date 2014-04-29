TEMPLATE = app

CONFIG = console

QT =

OBJECTS_DIR = .o
DESTDIR = ../bin

!win32 {
    LIBS += -L../lib
} else {
    QMAKE_CXXFLAGS += -EHsc
}

HEADERS += $$files(*.h)
SOURCES += $$files(*.cpp)
