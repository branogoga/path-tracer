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

TEST(Plane, texture_coordinates)
{
    auto planeXZ = Plane(Vector({0.0, 1.0, 0.0}), 0.0f);

    auto p1 = Point({0.0, 0.0, 0.0});
    auto uv1 = getTextureCoordinates(p1, planeXZ);
    EXPECT_FLOAT_EQ(0.0, uv1.u);
    EXPECT_FLOAT_EQ(0.0, uv1.v);

    auto p2 = Point({2.0, 0.0, 3.0});
    auto uv2 = getTextureCoordinates(p2, planeXZ);
    EXPECT_FLOAT_EQ(-3.0, uv2.u);
    EXPECT_FLOAT_EQ(-2.0, uv2.v);

    auto planeXY = Plane(Vector({0.0, 0.0, 1.0}), 0.0f);

    auto p3 = Point({2.0, 3.0, 0.0});
    auto uv3 = getTextureCoordinates(p3, planeXY);
    EXPECT_FLOAT_EQ(3.0, uv3.u);
    EXPECT_FLOAT_EQ(-2.0, uv3.v);

    auto planeYZ = Plane(Vector({1.0, 0.0, 0.0}), 0.0f);

    auto p4 = Point({0.0, 2.0, 3.0});
    auto uv4 = getTextureCoordinates(p4, planeYZ);
    EXPECT_FLOAT_EQ(3.0, uv4.u);
    EXPECT_FLOAT_EQ(-2.0, uv4.v);
}
