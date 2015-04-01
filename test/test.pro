TEMPLATE = lib

CONFIG *= static
SOURCES += test.cpp


QT *= core

include(../gtest/defines.pri)
include(../src/defines.pri)
include(../common.pri)
