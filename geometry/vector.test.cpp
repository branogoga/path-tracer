#include "vector.h"

#include "gtest/gtest.h"

TEST(Vector, createdWithZero)
{
    auto v = geometry::Vector();
    EXPECT_EQ(0.0f, v[0]);
    EXPECT_EQ(0.0f, v[1]);
    EXPECT_EQ(0.0f, v[2]);
}
