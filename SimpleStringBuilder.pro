TEMPLATE = app
TARGET = SimpleStringBuilder
INCLUDEPATH += .
QT += core
CONFIG += console c++11
QMAKE_CXXFLAGS *= $$(CXX_FLAGS)
QMAKE_LFLAGS *= $$(CXX_LINKER_FLAGS)
DESTDIR = bin

msvc {
  QMAKE_CFLAGS_WARN_ON -= -W3
  QMAKE_CFLAGS_WARN_ON += -W4
}

Release:DESTDIR = $${DESTDIR}/release
Release:OBJECTS_DIR = $${DESTDIR}/.obj
Release:MOC_DIR = $${DESTDIR}/.moc
Release:RCC_DIR = $${DESTDIR}/.rcc
Release:UI_DIR = $${DESTDIR}/.ui

Debug:DESTDIR = $${DESTDIR}/debug
Debug:OBJECTS_DIR = $${DESTDIR}/.obj
Debug:MOC_DIR = $${DESTDIR}/.moc
Debug:RCC_DIR = $${DESTDIR}/.rcc
Debug:UI_DIR = $${DESTDIR}/.ui

# Input
SOURCES += src/main.cpp

HEADERS += src/BaseStringBuilder.h
HEADERS += src/QStringBuilder.h
HEADERS += src/BasicStringBuilder.h

