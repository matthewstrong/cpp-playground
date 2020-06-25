#pragma once
#include "EnumHelpers.h"

namespace test_enums {

enum class Color
{
    red,
    green = 20,
    blue
};

using enum_helpers::EnumLookupException;
using enum_helpers::to_string;
using enum_helpers::to_integral;

GENERATE_ENUM_HELPERS(Color, red, green, blue);

} // namespace test_enums
