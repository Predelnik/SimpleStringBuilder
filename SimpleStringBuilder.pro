TEMPLATE = app
TARGET = SimpleStringBuilder
INCLUDEPATH += .
QT += core
CONFIG += console
msvc {
  QMAKE_CFLAGS_WARN_ON -= -W3
  QMAKE_CFLAGS_WARN_ON += -W4
}

# Input
HEADERS += SimpleStringBuilder.h
SOURCES += SimpleStringBuilder.cpp
