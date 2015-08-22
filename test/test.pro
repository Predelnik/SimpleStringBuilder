TEMPLATE = app

SOURCES += TestMain.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gtest/release -lgtest
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gtest/debug -lgtest
else:unix: LIBS += -L$$OUT_PWD/../gtest -lgtest

CONFIG *= console
QT *= core

include(../gtest/defines.pri)
include(../src/defines.pri)
include(../common.pri)
