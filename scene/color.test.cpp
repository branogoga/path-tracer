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
