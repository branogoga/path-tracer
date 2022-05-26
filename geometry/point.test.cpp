#include "axis.h"
#include "point.h"
#include "vector.h"

#include "gtest/gtest.h"

#include <cmath>

using namespace geometry;

void EXPECT_POINT_EQ(Point expected, Point result) {
    EXPECT_EQ(expected.dimension(), result.dimension());
    for(size_t i = 0; i < result.dimension(); ++i) {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}

TEST(Point, component_assignment)
{
    auto v = Point();
    v[Axis::X] = 1.0f;
    EXPECT_EQ(1.0f, v[Axis::X]);

    v[Axis::Y] = 2.0f;
    EXPECT_EQ(2.0f, v[Axis::Y]);

    v[Axis::Z] = 5.0f;
    EXPECT_EQ(5.0f, v[Axis::Z]);
}

TEST(Point, assignment)
{
    auto v1 = Point({1.0f, 2.0f, 3.0f});
    auto v2 = v1;
    v1[Axis::X] = 7.0f;
    EXPECT_EQ(1.0f, v2[Axis::X]);
    EXPECT_EQ(2.0f, v2[Axis::Y]);
    EXPECT_EQ(3.0f, v2[Axis::Z]);
}

TEST(Point, comparison)
{
    EXPECT_TRUE(Point({1.0f, 2.0f, 3.0f}) == Point({1.0f, 2.0f, 3.0f}));
    EXPECT_FALSE(Point({1.0f, 2.0f, 3.0f}) != Point({1.0f, 2.0f, 3.0f}));

    EXPECT_FALSE(Point({1.0f, 2.0f, 3.0f}) == Point({7.0f, 2.0f, 3.0f}));
    EXPECT_TRUE(Point({1.0f, 2.0f, 3.0f}) != Point({7.0f, 2.0f, 3.0f}));

    EXPECT_FALSE(Point({1.0f, 2.0f, 3.0f}) == Point({1.0f, 7.0f, 3.0f}));
    EXPECT_TRUE(Point({1.0f, 2.0f, 3.0f}) != Point({1.0f, 7.0f, 3.0f}));

    EXPECT_FALSE(Point({1.0f, 2.0f, 3.0f}) == Point({1.0f, 2.0f, 7.0f}));
    EXPECT_TRUE(Point({1.0f, 2.0f, 3.0f}) != Point({1.0f, 2.0f, 7.0f}));
}

TEST(Point, floating_point_comparison)
{
    EXPECT_FALSE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f + 1E-05, 2.0f, 3.0f}), 1E-06));
    EXPECT_FALSE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f + 2E-06, 2.0f, 3.0f}), 1E-06));
    EXPECT_FALSE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f, 2.0f + 2E-06, 3.0f}), 1E-06));
    EXPECT_FALSE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f, 2.0f, 3.0f + 2E-06}), 1E-06));
    EXPECT_TRUE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f + 1E-06, 2.0f, 3.0f}), 1E-06));
    EXPECT_TRUE(isEqual(Point({1.0f, 2.0f, 3.0f}), Point({1.0f + 1E-06, 2.0f + 1E-06, 3.0f + 1E-06}), 1E-06));
}

TEST(Point, addition)
{
    auto v1 = Point({1.0f, 2.0f, 3.0f});
    auto v2 = Vector({7.0f, 5.0f, 9.0f});
    auto v3 = v1 + v2;

    EXPECT_EQ(8.0f, v3[Axis::X]);
    EXPECT_EQ(7.0f, v3[Axis::Y]);
    EXPECT_EQ(12.0f, v3[Axis::Z]);
    EXPECT_TRUE(Point({8.0f, 7.0f, 12.0f})==v3);
}

TEST(Point, subtract)
{
    auto v1 = Point({1.0f, 2.0f, 3.0f});
    auto v2 = Point({7.0f, 5.0f, 9.0f});
    auto v3 = v2 - v1;

    EXPECT_EQ(6.0f, v3[Axis::X]);
    EXPECT_EQ(3.0f, v3[Axis::Y]);
    EXPECT_EQ(6.0f, v3[Axis::Z]);
    EXPECT_TRUE(Vector({6.0f, 3.0f, 6.0f})==v3);
}

TEST(Point, scaling)
{
    auto v1 = Point({1.0f, 2.0f, 3.0f});
    auto v2 = 10 * v1;

    EXPECT_EQ(10.0f, v2[Axis::X]);
    EXPECT_EQ(20.0f, v2[Axis::Y]);
    EXPECT_EQ(30.0f, v2[Axis::Z]);

    auto v3 = v1 * 10;

    EXPECT_EQ(10.0f, v3[Axis::X]);
    EXPECT_EQ(20.0f, v3[Axis::Y]);
    EXPECT_EQ(30.0f, v3[Axis::Z]);
}


