TEMPLATE = subdirs
SUBDIRS = gtest\
		  test \
		  main \

main.subdir = src
gtest.depends = test
gtest.depends = main

TARGET = SimpleStringBuilder
DESTDIR = bin

msvc {
  QMAKE_CFLAGS_WARN_ON -= -W3
  QMAKE_CFLAGS_WARN_ON += -W4
}


