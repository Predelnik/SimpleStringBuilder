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
  s = QStringBuilder{ "%1 %2 %3\n%4 %5 %6" }.setFieldWidth (10).arg ("Test", "Test", "Test").setFieldWidth (-10).arg ("Test", "Test", "Test");
  output << s << '\n';
  s = QStringBuilder{ "%1 %2 %3 %4 %5 %6" }.setFieldWidth (10).setFillChar ('_').setFloatingPointFormat ('g', 5).arg (12.123, 0.00005).
    setFloatingPointFormat ('f').setPrecision (5).arg (12.123, 0.00005).setFloatingPointFormat ('e', 6).arg (12.123, 0.00005);
  output << s << '\n';
  s = QStringBuilder{ "%1\n%2\n%3\n%4" }.setFieldWidth (25).setFillChar ('_').setIntegerBase (2).arg (12312312u).setIntegerBase (3).arg (12312312u).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  output << s << '\n';
  s = QStringBuilder{ "%1 %2 %3 %4" }.setIntegerBase (16).arg (10000000).setIntegerBase (36).arg (10000000).setIntegerBase (13).arg (10000000).setIntegerBase (35).arg (10000000);
  output << s << '\n';
  s = QStringBuilder{ "%9 %28 %7 %13 %1" }.arg (1, 2, 3, 4, 5);
  output << s << '\n';
}

void stdStringTest ()
{
  std::string s = StdStringBuilder{ "It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2).arg (3.5).arg ('G').arg ("Some kind of string");
  std::cout << s << '\n';
  s = StdStringBuilder{ "It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2, 3.5, 'G', "Some kind of string");
  std::cout << s << '\n';
  s = StdStringBuilder{ "%1 %2 %3 %4" }.setIntegerBase (2).arg (8).setIntegerBase (3).arg (8).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  std::cout << s << '\n';
  s = StdStringBuilder{ "%1 %2 %3\n%4 %5 %6" }.setFieldWidth (10).arg ("Test", "Test", "Test").setFieldWidth (-10).arg ("Test", "Test", "Test");
  std::cout << s << '\n';
  s = StdStringBuilder{ "%1 %2 %3 %4 %5 %6" }.setFieldWidth (10).setFillChar ('_').setFloatingPointFormat ('g', 5).arg (12.123, 0.00005).
    setFloatingPointFormat ('f').setPrecision (5).arg (12.123, 0.00005).setFloatingPointFormat ('e', 6).arg (12.123, 0.00005);
  std::cout << s << '\n';
  s = StdStringBuilder{ "%1\n%2\n%3\n%4" }.setFieldWidth (25).setFillChar ('_').setIntegerBase (2).arg (12312312u).setIntegerBase (3).arg (12312312u).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  std::cout << s << '\n';
  s = StdStringBuilder{ "%1 %2 %3 %4" }.setIntegerBase (16).arg (10000000).setIntegerBase (36).arg (10000000).setIntegerBase (13).arg (10000000).setIntegerBase (35).arg (10000000);
  std::cout << s << '\n';
  s = StdStringBuilder{ "%9 %28 %7 %13 %1" }.arg (1, 2, 3, 4, 5);
  std::cout << s << '\n';
}

void stdWstringTest ()
{
  std::wstring s = StdWstringBuilder{ L"It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2).arg (3.5).arg (L'G').arg (L"Some kind of string");
  std::wcout << s << '\n';
  s = StdWstringBuilder{L"It's test %1 we're testing %2 arg function %3. Does it work? %4" }.arg (2, 3.5, L'G', L"Some kind of string");
  std::wcout << s << '\n';
  s = StdWstringBuilder{ L"%1 %2 %3 %4" }.setIntegerBase (2).arg (8).setIntegerBase (3).arg (8).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  std::wcout << s << '\n';
   s = StdWstringBuilder{ L"%1 %2 %3\n%4 %5 %6" }.setFieldWidth (10).arg (L"Test", L"Test", L"Test").setFieldWidth (-10).arg (L"Test", L"Test", L"Test");
  std::wcout << s << '\n';
  s = StdWstringBuilder{ L"%1 %2 %3 %4 %5 %6" }.setFieldWidth (10).setFillChar (L'_').setFloatingPointFormat ('g', 5).arg (12.123, 0.00005).
    setFloatingPointFormat ('f').setPrecision (5).arg (12.123, 0.00005).setFloatingPointFormat ('e', 6).arg (12.123, 0.00005);
  std::wcout << s << '\n';
  s = StdWstringBuilder{ L"%1\n%2\n%3\n%4" }.setFieldWidth (25).setFillChar (L'_').setIntegerBase (2).arg (12312312u).setIntegerBase (3).arg (12312312u).setIntegerBase (4).arg (8).setIntegerBase (5).arg (8);
  std::wcout << s << '\n';
  s = StdWstringBuilder{ L"%1 %2 %3 %4" }.setIntegerBase (16).arg (10000000).setIntegerBase (36).arg (10000000).setIntegerBase (13).arg (10000000).setIntegerBase (35).arg (10000000);
  std::wcout << s << '\n';
  s = StdWstringBuilder{ L"%9 %28 %7 %13 %1" }.arg (1, 2, 3, 4, 5);
  std::wcout << s << '\n';
}

int main (void)
{
  #ifdef _MSC_VER
  _set_output_format (_TWO_DIGIT_EXPONENT); // Microsoft specific, to unify behavior with Qt
  #endif _MSC_VER

  std::cout << "QString\n";
  qStringTest ();
  std::cout << "std::string\n";
  stdStringTest ();
  std::cout << "std::wstring\n";
  stdWstringTest ();
}