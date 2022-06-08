#include "sphere.h"

#include "gtest/gtest.h"
#include "../geometry/axis.h"

using namespace geometry;

TEST(Sphere, hasIntersection)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({0.0f, 0.0f, -1.0f}));
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    EXPECT_TRUE(hasIntersection(ray, sphere));
}

TEST(Sphere, hasIntersection_no_intersect)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({1.0f, 0.0f, 0.0f}));
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    EXPECT_FALSE(hasIntersection(ray, sphere));
}

TEST(Sphere, getAllIntersections)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({0.0f, 0.0f, -1.0f}));
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto intersections = getAllIntersections(ray, sphere);
    EXPECT_EQ(2u, intersections.size());
    EXPECT_FLOAT_EQ(11.0, intersections[0]);
    EXPECT_FLOAT_EQ(9.0, intersections[1]);
}

TEST(Sphere, getAllIntersections_no_intersect)
{
    auto ray = Ray(Point({0.0f, 0.0f, 0.0f}), Vector({1.0f, 0.0f, 0.0f}));
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto intersections = getAllIntersections(ray, sphere);
    EXPECT_EQ(0u, intersections.size());
}

TEST(Sphere, normal_positive_z_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({0.0, 0.0, -9.0}), sphere);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(1.0, normal[Axis::Z]);
}

TEST(Sphere, normal_negative_z_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({0.0, 0.0, -11.0}), sphere);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(-1.0, normal[Axis::Z]);
}

TEST(Sphere, normal_positive_x_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({1.0, 0.0, -10.0}), sphere);
    EXPECT_FLOAT_EQ(1.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Z]);
}

TEST(Sphere, normal_negative_x_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({-1.0, 0.0, -10.0}), sphere);
    EXPECT_FLOAT_EQ(-1.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Z]);
}

TEST(Sphere, normal_positive_y_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({0.0, 1.0, -10.0}), sphere);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(1.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Z]);
}

TEST(Sphere, normal_negative_y_axis)
{
    auto sphere = Sphere(Point({0.0, 0.0, -10.0}), 1.0f);
    auto normal = getNormal(Point({0.0, -1.0, -10.0}), sphere);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0, normal[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, normal[Axis::Z]);
}
