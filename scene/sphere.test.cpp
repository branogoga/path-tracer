#include "sphere.h"

#include "gtest/gtest.h"

TEST(Sphere, intersect)
{
    auto ray = geometry::Ray(geometry::Point({0.0f, 0.0f, 0.0f}), geometry::Vector({0.0f, 0.0f, -1.0f}));
    auto sphere = Sphere(geometry::Point({0.0, 0.0, -10.0}), 1.0f);
    EXPECT_TRUE(intersect(ray, sphere));
}

TEST(Sphere, no_intersect)
{
    auto ray = geometry::Ray(geometry::Point({0.0f, 0.0f, 0.0f}), geometry::Vector({1.0f, 0.0f, 0.0f}));
    auto sphere = Sphere(geometry::Point({0.0, 0.0, -10.0}), 1.0f);
    EXPECT_FALSE(intersect(ray, sphere));
}
