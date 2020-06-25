// C++ headers
#include <utility>
#include <string>
// Third-party headers
#include <gtest/gtest.h>
// Project headers
#include "TestEnums.h"

using namespace test_enums;

typedef std::pair<test_enums::Color, std::string> Param;
class EnumHelperTests : public ::testing::TestWithParam<Param> {};

TEST_P( EnumHelperTests, EnumToString )
{
    // Get the parameterized test inputs
    Color enum_value = std::get<0>(GetParam());
    std::string str_value = std::get<1>(GetParam());

    // Test the stream operator
    std::ostringstream oss;
    ASSERT_NO_THROW(oss << enum_value);
    EXPECT_EQ(str_value, oss.str());

    // Test conversion from enum value to string
    EXPECT_EQ(str_value, to_string(enum_value));

    // Test invalid enum value conversion to string
    EXPECT_THROW(to_string((Color)500), EnumLookupException);
}

TEST_P( EnumHelperTests, StringToEnum )
{
    // Get the parameterized test inputs
    Color enum_value = std::get<0>(GetParam());
    std::string str_value = std::get<1>(GetParam());

    // Test to conversion from string value to enum
    EXPECT_EQ(enum_value, to_enum<Color>(str_value));
    // Test to conversion from string value to enum
    EXPECT_EQ(enum_value, to_enum<Color>("Color::" + str_value));
    // Test invalid strings to enum conversion
    EXPECT_THROW(to_enum<Color>("INVALID_VALUE"), EnumLookupException);
}

TEST_P( EnumHelperTests, IntegralConversion )
{
    // Get the parameterized test inputs
    Color enum_value = std::get<0>(GetParam());

    // Test conversion from enum <-> integral values
    auto i = to_integral(enum_value);
    EXPECT_EQ(enum_value, static_cast<Color>(i));
}

INSTANTIATE_TEST_SUITE_P(
    TestSuite,
    EnumHelperTests,
    ::testing::Values(
        Param{ Color::red,   "red" },
        Param{ Color::green, "green" },
        Param{ Color::blue,  "blue" })
);

TEST (ToIntegralTests, CheckEnumValues)
{
    EXPECT_EQ (to_integral(Color::red), 0);
    EXPECT_EQ (to_integral(Color::green), 20);
    EXPECT_EQ (to_integral(Color::blue), 21);
}
