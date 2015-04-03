#pragma once

#include <initializer_list>
#include <type_traits>
#include <utility>
#include <assert.h>

// applyArg should be overloaded for string type desirably at least in the
// following forms:
// applyIntegralArg(BaseStringBuilderAdapter::StringTag<StringType>, StringType
// &, IntegralType value, int fieldWidth, int base,
// CharType
// fillChar)
// applyArg(BaseStringBuilderAdapter::StringTag<StringType>, StringType &,
// CharType value, int fieldWidth, CharType fillChar)
// applyArg(BaseStringBuilderAdapter::StringTag<StringType>, StringType &, const
// StringType &value, int fieldWidth, CharType
// fillChar)
// applyArg(BaseStringBuilderAdapter::StringTag<StringType>, StringType &,
// double value, int fieldWidth, char
// floatingPointFormat, int precision, CharType fillChar)
// overloads should be placed in namespace `BaseStringBuilderAdapter`

// If some functions are not used they may not be defined

namespace BaseStringBuilderAdapter {
struct StringTagBase {};
template <typename StringType>
struct StringTag : StringTagBase {};

template <typename... Args>
void applyArg(StringTagBase, Args &&...) {
  assert(false);
}

template <typename... Args>
void applyIntegralArg(StringTagBase, Args &&...) {
  assert(false);
}
}

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
  StringType toString() { return m_string; }
  operator StringType() { return toString(); }

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

  // for integral but not character types
  template <typename Type>
  BaseStringBuilder &arg(Type &&value) {
    integralCheck(std::forward<Type>(value), typename std::is_integral<Type>::type{});
    return *this;
  }

  template <
      typename... ArgTypes,
      typename = typename std::enable_if<
          sizeof...(ArgTypes) != 1 && sizeof...(ArgTypes) != 0, void>::type>
  BaseStringBuilder &arg(ArgTypes &&... args) {
    static_cast<void>(
        std::initializer_list<int>{(arg(std::forward<ArgTypes>(args)), 0)...});
    return *this;
  }

 private:
  template <typename Type>
  void integralCheck(Type &&value, std::true_type) {
    applyIntegralPrivate(std::forward<Type>(value));
  }

  template <typename Type>
  void integralCheck(Type &&value, std::false_type) {
    argPrivate(std::forward<Type>(value));
  }

  template <typename IntegralType>
  void applyIntegralPrivate(IntegralType value) {
    applyIntegralArg(BaseStringBuilderAdapter::StringTag<StringType>{},
                     m_string, value, m_fieldWidth, m_base, m_fillChar);
  }

  void applyIntegralPrivate(char value) {
    argPrivate(typename StringType::value_type{value});
  }

  void applyIntegralPrivate(wchar_t value) {
    argPrivate(typename StringType::value_type{value});
  }

  BaseStringBuilder &argPrivate(typename StringType::value_type value) {
    applyArg(BaseStringBuilderAdapter::StringTag<StringType>{}, m_string, value,
             m_fieldWidth, m_fillChar);
    return *this;
  }

  BaseStringBuilder &argPrivate(double value) {
    applyArg(BaseStringBuilderAdapter::StringTag<StringType>{}, m_string, value,
             m_fieldWidth, m_floatingPointFormat, m_precision, m_fillChar);
    return *this;
  }

  BaseStringBuilder &argPrivate(const StringType &value) {
    applyArg(BaseStringBuilderAdapter::StringTag<StringType>{}, m_string, value,
             m_fieldWidth, m_fillChar);
    return *this;
  }

 private:
  StringType m_string;
  int m_fieldWidth = 0;
  typename StringType::value_type m_fillChar = ' ';
  int m_base = 10;
  int m_precision = -1;
  char m_floatingPointFormat = 'g';
};