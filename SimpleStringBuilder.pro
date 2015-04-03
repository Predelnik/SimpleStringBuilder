TEMPLATE = subdirs
SUBDIRS = gtest\
		  test \
		  main \

main.subdir = src
test.depends = gtest main

TARGET = SimpleStringBuilder
DESTDIR = bin

include(common.pri)

msvc {
  QMAKE_CFLAGS_WARN_ON -= -W3
  QMAKE_CFLAGS_WARN_ON += -W4
}


