TEMPLATE = lib

CONFIG *= static
SOURCES += test.cpp

QMAKE_CXXFLAGS *= $$(CXX_FLAGS)
QMAKE_LFLAGS *= $$(CXX_LINKER_FLAGS)

QT *= core
CONFIG *= c++11

include(../gtest/defines.pri)
include(../src/defines.pri)

msvc {
  QMAKE_CFLAGS_WARN_ON -= -W3
  QMAKE_CFLAGS_WARN_ON += -W4
}
