#pragma once

#include "BaseStringBuilder.h"

#include <limits>
#include <regex>
#include <string>
#include <assert.h>

namespace BaseStringBuilderDetail {
template <typename CharType>
struct applyArgBasicStringImpl {
  using StringType = std::basic_string<CharType>;
  using ConstItType = typename StringType::const_iterator;

  static void applyArg(StringType &str, const StringType &arg, int fieldWidth,
                       CharType fillChar) {
    std::basic_regex<CharType> pattern(R"(\%(\d+))");
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
      std::string beautifiedArg = arg;
      beautifiedArg.insert(
          beautifiedArg.begin(),
          std::max(fieldWidth - static_cast<int>(arg.length()), 0), fillChar);
      str.replace(lowestPattern.second.first, lowestPattern.second.second,
                  beautifiedArg);
    } else {
      assert(false);  // Pattern was not applied
    }
  }
};  // struct applyArgBasicStringImpl

template <typename CharType, typename... ArgTypes>
void applyArg(std::basic_string<CharType> &str, ArgTypes &&... args) {
  applyArgBasicStringImpl<CharType>::applyArg(str,
                                              std::forward<ArgTypes>(args)...);
}

}  // namespace BaseStringBuilderDetail

using StdStringBuilder = BaseStringBuilder<std::string>;
using StdWstringBuilder = BaseStringBuilder<std::string>;
