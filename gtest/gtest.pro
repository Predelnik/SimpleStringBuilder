TEMPLATE = app
TARGET = gtest

SOURCES *= gtest_main.cc \
           gtest-all.cc
HEADERS *= gtest.h

CONFIG *= console

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../test/release -ltest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../test/debug -ltest
else:unix: LIBS += -L$$OUT_PWD/../test/release -ltest



QMAKE_CXXFLAGS *= $$(CXX_FLAGS)
QMAKE_LFLAGS *= $$(CXX_LINKER_FLAGS)
msvc {
  QMAKE_LFLAGS *= /OPT:REF
}

include(defines.pri)