#include "plane.h"

#include "gtest/gtest.h"
#include "../geometry/axis.h"

using namespace geometry;

TEST(Plane, hasIntersection)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({0.0f, -1.0f, -1.0f}));
    auto plane = Plane(Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_TRUE(hasIntersection(ray, plane));
}

TEST(Plane, hasIntersection_intersect_behind)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({0.0f, +1.0f, -1.0f}));
    auto plane = Plane(Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_FALSE(hasIntersection(ray, plane));
}

TEST(Plane, hasIntersection_no_intersect)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({0.0f, 0.0f, -1.0f}));
    auto plane = Plane(Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_FALSE(hasIntersection(ray, plane));
}

TEST(Plane, normal)
{
    auto plane = Plane(Vector({0.0, 1.0, 0.0}), -1.0f);
    auto normal = getNormal(Point(), plane);
    EXPECT_FLOAT_EQ(normal[Axis::X], normal[Axis::X]);
}
