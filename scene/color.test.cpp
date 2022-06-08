#include "color.h"

#include "gtest/gtest.h"

TEST(Color, createFromFloats)
{
    auto c = Color(1.0, 0.0, 0.27, 0.35);
    EXPECT_FLOAT_EQ(1.0, c[Color::R]);
    EXPECT_FLOAT_EQ(0.0, c[Color::G]);
    EXPECT_FLOAT_EQ(0.27, c[Color::B]);
    EXPECT_FLOAT_EQ(0.35, c[Color::A]);
}

TEST(Color, multiply_by_constant)
{
    auto c = Color(0.35, 0.0, 0.27, 1.0);
    auto result = 0.5 * c;
    EXPECT_FLOAT_EQ(0.175, result[Color::R]);
    EXPECT_FLOAT_EQ(0.0, result[Color::G]);
    EXPECT_FLOAT_EQ(0.135, result[Color::B]);
    EXPECT_FLOAT_EQ(1.0, result[Color::A]);
}
