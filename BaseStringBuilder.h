#pragma once

#include <initializer_list>
#include <type_traits>

// applyArg should be overloaded for string type in following forms:
// applyArg(StringType &, IntegralType value, int fieldWidth, int base, CharType
// fillChar)
// applyArg(StringType &, CharType value, int fieldWidth, CharType fillChar)
// applyArg(StringType &, const StringType &value, int fieldWidth, CharType
// fillChar)
// applyArg(StringType &, double value, char floatingPointFormat, int
// fieldWidth, CharType fillChar)

// If some functions are not used they may not be defined

template <typename StringType>
class BaseStringBuilder {
 public:
  // Initialization:

  BaseStringBuilder(const StringType &string) { operator()(string); }
  BaseStringBuilder &operator()(const StringType &string) {
    m_string = string;
    return *this;
  }

  // Output:
  operator StringType() { return m_string; }

  // Modifying state:
  BaseStringBuilder &setFieldWidth(int fieldWidth) {
    m_fieldWidth = fieldWidth;
    return *this;
  }
  BaseStringBuilder &setFillChar(typename StringType::value_type fillChar) {
    m_fillChar = fillChar;
    return *this;
  }
  BaseStringBuilder &setIntegerBase(int base) {
    m_base = base;
    return *this;
  }
  BaseStringBuilder &setPrecision(int precision) {
    m_precision = precision;
    return *this;
  }
  BaseStringBuilder &setFloatingPointFormat(char format) {
    m_floatingPointFormat = format;
    return *this;
  }

  BaseStringBuilder &setFloatingPointFormat(char format, int precision) {
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
  BaseStringBuilder &arg(Integral value) {
    applyArg(m_string, value, m_fieldWidth, m_base, m_fillChar);
    return *this;
  }

  // specialization for char
  template <>
  BaseStringBuilder &arg<char, 0>(char value) {
    return (arg(typename StringType::value_type{value}));
  }

  BaseStringBuilder &arg(typename StringType::value_type value) {
    applyArg(m_string, value, m_fieldWidth, m_fillChar);
    return *this;
  }

  BaseStringBuilder &arg(double value) {
    applyArg(m_string, value, m_fieldWidth, m_floatingPointFormat, m_precision,
             m_fillChar);
    return *this;
  }

  BaseStringBuilder &arg(const StringType &value) {
    applyArg(m_string, value, m_fieldWidth, m_fillChar);
    return *this;
  }

  template <typename... ArgTypes, typename = typename std::enable_if<
                                      sizeof...(ArgTypes) != 1, void>::type>
  BaseStringBuilder &arg(ArgTypes &&... args) {
    std::initializer_list<int>{(arg(std::forward<ArgTypes>(args)), 0)...};
    return *this;
  }

 private:
  StringType m_string;
  int m_fieldWidth = 0;
  typename StringType::value_type m_fillChar = QLatin1Char(' ');
  int m_base = 10;
  int m_precision = -1;
  char m_floatingPointFormat = 'g';
};