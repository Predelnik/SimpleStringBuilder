#include "BasicStringBuilder.h"
#include "QStringBuilder.h"

#include <QDebug>

#include <iostream>

void qStringTest ()
{
  QTextStream output (stdout);
  QString s = QStringBuilder{ "It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2).arg (3.5).arg ('G').arg ("Some kind of string");
  output << s << '\n';
  s = QStringBuilder{ "It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2, 3.5, 'G', "Some kind of string");
  output << s << '\n';
  s = QStringBuilder{ "%1 %2 %3 %4" }.setIntegerBase (2).arg (8).setIntegerBase (3).arg (8).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  output << s << '\n';
  s = QStringBuilder{ "%1 %2 %3\n%4 %5 %6" }.setFieldWidth (10).arg ("Test", "Test", "Test").setFieldWidth (5).arg ("Test", "Test", "Test");
  output << s << '\n';
  s = QStringBuilder{ "%1 %2 %3 %4 %5 %6" }.setFieldWidth (10).setFillChar ('_').setFloatingPointFormat ('g', 5).arg (12.123, 0.00005).
    setFloatingPointFormat ('f').setPrecision (5).arg (12.123, 0.00005).setFloatingPointFormat ('e', 6).arg (12.123, 0.00005);
  output << s << '\n';
  s = QStringBuilder{ "%1\n%2\n%3\n%4" }.setFieldWidth (25).setFillChar ('_').setIntegerBase (2).arg (12312312u).setIntegerBase (3).arg (12312312u).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  output << s << '\n';
}

void basicStringTest ()
{
  std::string s = StdStringBuilder{ "It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg ("2").arg ("3.5").arg ("G").arg ("Some kind of string");
  std::cout << s << '\n';
}

int main (void)
{
  basicStringTest ();
}