#pragma once

#include "BaseStringBuilder.h"

#include <iomanip>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <assert.h>

namespace BaseStringBuilderAdapter {

template <typename CharType> struct ApplyArgBasicStringImpl {
  using StringType = std::basic_string<CharType>;
  using ConstItType = typename StringType::const_iterator;

  static void applyArg(StringType &str, const StringType &arg, int fieldWidth,
                       CharType fillChar) {
    auto lowestPattern = std::make_pair(
        std::numeric_limits<int>::max(),
        std::make_pair(str.cend(), str.cend())); // lowest out of %1, %2 etc.
    {
      std::string r = R"(\%(\d+))";
      std::basic_regex<CharType> pattern(StringType(r.begin(), r.end()));

      auto itBegin =
          std::regex_iterator<ConstItType>(str.begin(), str.end(), pattern);
      auto itEnd = std::regex_iterator<ConstItType>{};

      for (auto it = itBegin; it != itEnd; ++it) {
        auto &sm = *it;
        try {
          int result = std::stoi(sm[1].str());
          if (result >= 0)
            lowestPattern =
                std::min(lowestPattern,
                         std::make_pair(result, std::make_pair(sm[0].first,
                                                               sm[0].second)));
        } catch (...) {
          // We clearly shouldn't care about cases where we miss the pattern
        }
      }
    }
    {
      if (lowestPattern.second.first != str.cend()) {
        StringType beautifiedArg = arg;
        beautifiedArg.insert(
            fieldWidth > 0 ? beautifiedArg.begin() : beautifiedArg.end(),
            std::max(abs(fieldWidth) - static_cast<int>(arg.length()), 0),
            fillChar);
        std::string r = R"((?!\d))"; // Negative lookahead to prevent i.e. %13
                                     // be replace instead of %1
        std::basic_regex<CharType> pattern(
            StringType(lowestPattern.second.first,
                       lowestPattern.second.second) +
            StringType(r.begin(), r.end()));
        str = std::regex_replace(str, pattern, beautifiedArg);
      } else {
        assert(false); // Pattern was not applied
      }
    }
  }

  static void applyArg(StringType &str, CharType value, int fieldWidth,
                       CharType fillChar) {
    applyArg(str, StringType(1, value), fieldWidth, fillChar);
  }

  template <typename IntegralType>
  static std::basic_string<CharType> toStringInBase(IntegralType val,
                                                    int base) {
    if (base < 2 || base > 36) {
      assert(false); // Wrong base was used
      base = 10;
    }

    std::basic_string<CharType> result;
    while (val > 0) {
      auto digit = val % base;
      CharType ch;
      if (digit < 10)
        ch = CharType{'0'} + digit;
      else
        ch = CharType{'a'} + digit - 10;
      result.push_back(ch);
      val /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  template <typename IntegralType>
  static void applyIntegralArg(StringType &str, IntegralType value,
                               int fieldWidth, int base, CharType fillChar) {
    applyArg(str, toStringInBase(value, base), fieldWidth, fillChar);
  }

  static void applyArg(StringType &str, double value, int fieldWidth,
                       char floatingPointFormat, int precision,
                       CharType fillChar) {
    std::basic_stringstream<CharType> sstream;
    sstream << std::setprecision(precision);
    switch (floatingPointFormat) {
    case 'f':
      sstream << std::fixed;
      break;
    case 'e':
      sstream << std::scientific;
      break;
    }
    sstream << value;
    applyArg(str, sstream.str(), fieldWidth, fillChar);
  }
}; // struct applyArgBasicStringImpl

template <typename CharType, typename... ArgTypes>
void applyArg(StringTag<std::basic_string<CharType>>, ArgTypes &&... args) {
  ApplyArgBasicStringImpl<CharType>::applyArg(std::forward<ArgTypes>(args)...);
}

template <typename CharType, typename... ArgTypes>
void applyIntegralArg(StringTag<std::basic_string<CharType>>,
                      ArgTypes &&... args) {
  ApplyArgBasicStringImpl<CharType>::applyIntegralArg(
      std::forward<ArgTypes>(args)...);
}

} // namespace BaseStringBuilderDetail

using StdStringBuilder = BaseStringBuilder<std::string>;
using StdWstringBuilder = BaseStringBuilder<std::wstring>;
