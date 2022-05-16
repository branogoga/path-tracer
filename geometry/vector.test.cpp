#include "vector.h"

#include "gtest/gtest.h"

using namespace geometry;

TEST(Vector, assignment)
{
    auto v = Vector();
    v[Axis::X] = 1.0f;
    EXPECT_EQ(1.0f, v[Axis::X]);

    v[Axis::Y] = 2.0f;
    EXPECT_EQ(2.0f, v[Axis::Y]);

    v[Axis::Z] = 5.0f;
    EXPECT_EQ(5.0f, v[Axis::Z]);
}
