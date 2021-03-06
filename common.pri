win32 {
    BOOST_PATH = $$(BOOST_PATH)
    BOOST_LIB_PATH = $$(BOOST_LIB_PATH)

    isEmpty(BOOST_PATH) {
            error(BOOST_PATH environment varaible not set)
    }

    isEmpty(BOOST_LIB_PATH) {
            BOOST_LIB_PATH = $$BOOST_PATH/stage/lib
    }

    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$BOOST_LIB_PATH
    DEFINES += _WIN32_WINNT=0x0600
    DEFINES += _SCL_SECURE_NO_WARNINGS
    DEFINES += _CRT_SECURE_NO_WARNINGS
}
else {
    QMAKE_CXXFLAGS += -std=gnu++11
    LIBS += -lboost_system
}

DEFINES += PORT=42422

CONFIG -= qt
QT =

export(INCLUDEPATH)
export(LIBS)
export(DEFINES)
export(CONFIG)
export(QT)
