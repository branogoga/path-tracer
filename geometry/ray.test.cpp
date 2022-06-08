#include "ray.h"

#include "gtest/gtest.h"
#include "axis.h"

using namespace geometry;

TEST(Ray, evaluation)
{
    Ray ray(Point({1.0, 2.0, 3.0}), Vector({0.3, -0.25, 0.1}));

    auto p0 = ray(0);
    EXPECT_FLOAT_EQ(1.0, p0[Axis::X]);
    EXPECT_FLOAT_EQ(2.0, p0[Axis::Y]);
    EXPECT_FLOAT_EQ(3.0, p0[Axis::Z]);

    auto p1 = ray(1);
    EXPECT_FLOAT_EQ(1.3, p1[Axis::X]);
    EXPECT_FLOAT_EQ(1.75, p1[Axis::Y]);
    EXPECT_FLOAT_EQ(3.1, p1[Axis::Z]);

    auto p_1 = ray(-1);
    EXPECT_FLOAT_EQ(0.7, p_1[Axis::X]);
    EXPECT_FLOAT_EQ(2.25, p_1[Axis::Y]);
    EXPECT_FLOAT_EQ(2.9, p_1[Axis::Z]);

    auto p2 = ray(2);
    EXPECT_FLOAT_EQ(1.6, p2[Axis::X]);
    EXPECT_FLOAT_EQ(1.5, p2[Axis::Y]);
    EXPECT_FLOAT_EQ(3.2, p2[Axis::Z]);
}