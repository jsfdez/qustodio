BOOST_PATH = $$(BOOST_PATH)
BOOST_LIB_PATH = $$(BOOST_LIB_PATH)

isEmpty(BOOST_PATH) {
	error(BOOST_PATH environment varaible not set)
}

isEmpty(BOOST_LIB_PATH) {
	BOOST_LIB_PATH = $$BOOST_PATH/stage/lib
}

win32 {
    INCLUDEPATH += $$(BOOST_PATH)
    LIBS += -L$$BOOST_LIB_PATH
    DEFINES += _WIN32_WINNT=0x0600
}

export(INCLUDEPATH)
export(LIBS)
export(DEFINES)
