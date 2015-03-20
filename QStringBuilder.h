#pragma once

#include "BaseStringBuilder.h"
#include <QString>

namespace BaseStringBuilderDetail
{
template <typename... ArgTypes>
void applyArg (QString &string, ArgTypes&&... args)
{
  string = string.arg (std::forward<ArgTypes> (args)...);
}
}

using QStringBuilder = BaseStringBuilder<QString>;
