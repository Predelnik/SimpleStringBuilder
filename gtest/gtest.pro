TEMPLATE = lib
TARGET = gtest

SOURCES *= gtest-all.cc
HEADERS *= gtest.h

CONFIG *= static

linux {
  QMAKE_CXXFLAGS *= -Wno-missing-field-initializers
}


QMAKE_CXXFLAGS *= $$(CXX_FLAGS)
QMAKE_LFLAGS *= $$(CXX_LINKER_FLAGS)

include(defines.pri)
include(../common.pri)
