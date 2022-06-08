#include "plane.h"

#include "gtest/gtest.h"

TEST(Plane, intersect)
{
    auto ray = geometry::Ray(geometry::Point({0.0f, 0.0f, 0.0f}), geometry::Vector({0.0f, -1.0f, -1.0f}));
    auto plane = Plane(geometry::Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_TRUE(intersect(ray, plane));
}

TEST(Plane, intersect_behind)
{
    auto ray = geometry::Ray(geometry::Point({0.0f, 0.0f, 0.0f}), geometry::Vector({0.0f, +1.0f, -1.0f}));
    auto plane = Plane(geometry::Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_FALSE(intersect(ray, plane));
}

TEST(Plane, no_intersect)
{
    auto ray = geometry::Ray(geometry::Point({0.0f, 0.0f, 0.0f}), geometry::Vector({0.0f, 0.0f, -1.0f}));
    auto plane = Plane(geometry::Vector({0.0, 1.0, 0.0}), -1.0f);
    EXPECT_FALSE(intersect(ray, plane));
}

