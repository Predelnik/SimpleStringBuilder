#pragma once

#include "BaseStringBuilder.h"
#include <QString>

namespace BaseStringBuilderAdapter {
template <typename... ArgTypes>
void applyArg(StringTag<QString>, QString &string, ArgTypes &&... args) {
  string = string.arg(std::forward<ArgTypes>(args)...);
}
template <typename... ArgTypes>
void applyIntegralArg(StringTag<QString>, QString &string,
                      ArgTypes &&... args) {
  string = string.arg(std::forward<ArgTypes>(args)...);
}
}

using QStringBuilder = BaseStringBuilder<QString>;
