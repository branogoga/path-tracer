#include "material.h"

#include "gtest/gtest.h"

using namespace geometry;

TEST(Material, ambientLight)
{
    auto material = Material(Color(1.0, 1.0, 0.0), Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), 1.0, Color(0.1, 0.2, 0.3));

    auto color1 = material.calculateLighting(
            Point({0.0, 0.0, 0.0}),
            Vector({0.0, 1.0, 0.0}),
            Point({0.0, 0.0, 1.0}),
            Point({0.0, 0.0, 1.0}),
            Colors::White
    );
    EXPECT_FLOAT_EQ(0.1, color1[Color::R]);
    EXPECT_FLOAT_EQ(0.2, color1[Color::G]);
    EXPECT_FLOAT_EQ(0.0, color1[Color::B]);
}

TEST(Material, diffuseLightPerpendicularToSurfaceNormal) {
    auto material = Material(Color(1.0, 1.0, 0.0), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0), 1.0, Color(0.0, 0.0, 0.0));

    auto color = material.calculateLighting(
            Point({0.0, 0.0, 0.0}),
            Vector({0.0, 1.0, 0.0}),
            Point({0.0, 0.0, 1.0}),
            Point({0.0, 0.0, 1.0}),
            Colors::White
    );
    EXPECT_FLOAT_EQ(0.0, color[Color::R]);
    EXPECT_FLOAT_EQ(0.0, color[Color::G]);
    EXPECT_FLOAT_EQ(0.0, color[Color::B]);
}

TEST(Material, diffuseLightAboveSurface)
{
    auto material = Material(Color(1.0, 1.0, 0.0), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0), 1.0, Color(0.0, 0.0, 0.0));

    auto color = material.calculateLighting(
            Point({0.0, 0.0, 0.0}),
            Vector({0.0, 1.0, 0.0}),
            Point({0.0, 0.0, 1.0}),
            Point({0.0, 1.0, 0.0}),
            Colors::White
    );
    EXPECT_FLOAT_EQ(1.0, color[Color::R]);
    EXPECT_FLOAT_EQ(1.0, color[Color::G]);
    EXPECT_FLOAT_EQ(0.0, color[Color::B]);
}

TEST(Material, diffuseLightUnderSurface)
{
    auto material = Material(Color(1.0, 1.0, 0.0), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0), 1.0, Color(0.0, 0.0, 0.0));

    auto color = material.calculateLighting(
            Point({0.0, 0.0, 0.0}),
            Vector({0.0, 1.0, 0.0}),
            Point({0.0, 0.0, 1.0}),
            Point({0.0, -1.0, 0.0}),
            Colors::White
    );
    EXPECT_FLOAT_EQ(0.0, color[Color::R]);
    EXPECT_FLOAT_EQ(0.0, color[Color::G]);
    EXPECT_FLOAT_EQ(0.0, color[Color::B]);
}

TEST(Material, diffuseLight45DegreesToSurface)
{
    auto material = Material(Color(1.0, 1.0, 0.0), Color(1.0, 1.0, 1.0), Color(0.0, 0.0, 0.0), 1.0, Color(0.0, 0.0, 0.0));

    auto color = material.calculateLighting(
            Point({0.0, 0.0, 0.0}),
            Vector({0.0, 1.0, 0.0}),
            Point({0.0, 0.0, 1.0}),
            Point({1.0, 1.0, 0.0}),
            Colors::White
    );
    EXPECT_FLOAT_EQ(0.70710677, color[Color::R]);
    EXPECT_FLOAT_EQ(0.70710677, color[Color::G]);
    EXPECT_FLOAT_EQ(0.0, color[Color::B]);
}

