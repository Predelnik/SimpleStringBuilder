#pragma once

#include <QString>

#include <initializer_list>

class SimpleStringBuilder {
 public:
  // Initialization:

  SimpleStringBuilder(const QString &string) { operator()(string); }
  SimpleStringBuilder &operator()(const QString &string) {
    m_string = string;
    return *this;
  }

  // Output:
  operator QString() { return m_string; }

  // Modifying state:
  SimpleStringBuilder &setFieldWidth(int fieldWidth) {
    m_fieldWidth = fieldWidth;
    return *this;
  }
  SimpleStringBuilder &setFillChar(QChar fillChar) {
    m_fillChar = fillChar;
    return *this;
  }
  SimpleStringBuilder &setIntegerBase(int base) {
    m_base = base;
    return *this;
  }
  SimpleStringBuilder &setPrecision(int precision) {
    m_precision = precision;
    return *this;
  }
  SimpleStringBuilder &setFloatingPointFormat(char format) {
    m_floatingPointFormat = format;
    return *this;
  }

  SimpleStringBuilder &setFloatingPointFormat(char format, int precision) {
    m_floatingPointFormat = format;
    m_precision = precision;
    return *this;
  }

  // Arg:
  // function for int, technically it will give an error for certain values like
  // wchar_t
  template <
      typename Integral,
      typename std::enable_if<std::is_integral<Integral>::value, int>::type = 0>
  SimpleStringBuilder &arg(Integral value) {
    m_string = m_string.arg(value, m_fieldWidth, m_base, m_fillChar);
    return *this;
  }

  // specialization for char
  template <>
  SimpleStringBuilder &arg<char, 0>(char value) {
    return (arg(QChar{value}));
  }

  SimpleStringBuilder &arg(QChar value) {
    m_string = m_string.arg(value, m_fieldWidth, m_fillChar);
    return *this;
  }

  SimpleStringBuilder &arg(double value) {
    m_string = m_string.arg(value, m_fieldWidth, m_floatingPointFormat,
                            m_precision, m_fillChar);
    return *this;
  }

  SimpleStringBuilder &arg(const QString &value) {
    m_string = m_string.arg(value, m_fieldWidth, m_fillChar);
    return *this;
  }

  template <typename... ArgTypes, typename = typename std::enable_if<
                                      sizeof...(ArgTypes) != 1, void>::type>
  SimpleStringBuilder &arg(ArgTypes &&... args) {
    std::initializer_list<int>{(arg(std::forward<ArgTypes>(args)), 0)...};
    return *this;
  }

 private:
  QString m_string;
  int m_fieldWidth = 0;
  QChar m_fillChar = QLatin1Char(' ');
  int m_base = 10;
  int m_precision = -1;
  char m_floatingPointFormat = 'g';
};