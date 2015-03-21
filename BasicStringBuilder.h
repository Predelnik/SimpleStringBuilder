#pragma once

#include "BaseStringBuilder.h"

#include <iomanip>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <assert.h>

namespace BaseStringBuilderAdapter {
template <typename CharType>
struct applyArgBasicStringImpl {
  using StringType = std::basic_string<CharType>;
  using ConstItType = typename StringType::const_iterator;

  static void applyArg(StringType &str, const StringType &arg, int fieldWidth,
                       CharType fillChar) {
    std::string r = R"(\%(\d+))";
    std::basic_regex<CharType> pattern(StringType (r.begin (), r.end ()));
    auto lowestPattern = std::make_pair(
        std::numeric_limits<int>::max(),
        std::make_pair(str.cend(), str.cend()));  // lowest out of %1, %2 etc.

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
                       std::make_pair(
                           result, std::make_pair(sm[0].first, sm[0].second)));
      } catch (...) {
        // We clearly shouldn't care about cases where we miss the pattern
      }
    }

    if (lowestPattern.second.first != str.cend()) {
      StringType beautifiedArg = arg;
      beautifiedArg.insert(
          fieldWidth > 0 ? beautifiedArg.begin() : beautifiedArg.end (),
          std::max(abs (fieldWidth) - static_cast<int>(arg.length()), 0), fillChar);
      str.replace(lowestPattern.second.first, lowestPattern.second.second,
                  beautifiedArg);
    } else {
      assert(false);  // Pattern was not applied
    }
  }

  static void applyArg(StringType &str, CharType value, int fieldWidth,
                       CharType fillChar) {
    applyArg(str, StringType(1, value), fieldWidth, fillChar);
  }

  template <typename Integral>
  static std::basic_string<CharType> toStringInBase(Integral val, int base) {
    if (base < 2 || base > 36)
    {
      assert (false); // Wrong base was used
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

  template <
      typename Integral,
      typename std::enable_if<std::is_integral<Integral>::value, int>::type = 0>
  static void applyArg(StringType &str, Integral value, int fieldWidth,
                       int base, CharType fillChar) {
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
};  // struct applyArgBasicStringImpl

template <typename CharType, typename... ArgTypes>
void applyArg(std::basic_string<CharType> &str, ArgTypes &&... args) {
  applyArgBasicStringImpl<CharType>::applyArg(str,
                                              std::forward<ArgTypes>(args)...);
}

}  // namespace BaseStringBuilderDetail

using StdStringBuilder = BaseStringBuilder<std::string>;
using StdWstringBuilder = BaseStringBuilder<std::wstring>;
