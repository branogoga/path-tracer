#include "quadratic_solver.h"

#include "gtest/gtest.h"

TEST(QuadraticEquation, hasRoots_one)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, 0.0);
    EXPECT_TRUE(quadratic.hasRoot());
}

TEST(QuadraticEquation, hasRoots_two)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, -1.0);
    EXPECT_TRUE(quadratic.hasRoot());
}

TEST(QuadraticEquation, hasRoots_none)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, +1.0);
    EXPECT_FALSE(quadratic.hasRoot());
}

TEST(QuadraticEquation, numberOfRoots_one)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, 0.0);
    EXPECT_EQ(1u, quadratic.getNumberOfRoots());
}

TEST(QuadraticEquation, numberOfRoots_two)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, -1.0);
    EXPECT_EQ(2u, quadratic.getNumberOfRoots());
}

TEST(QuadraticEquation, numberOfRoots_none)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, +1.0);
    EXPECT_EQ(0u, quadratic.getNumberOfRoots());
}

TEST(QuadraticEquation, getRoots_one)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, 0.0);
    EXPECT_EQ(std::vector<float>({0.0f}), quadratic.getRoots());
}

TEST(QuadraticEquation, getRoots_two)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, -1.0);
    EXPECT_EQ(std::vector<float>({+1.0f, -1.0f}), quadratic.getRoots());
}

TEST(QuadraticEquation, getRoots_none)
{
    auto quadratic = QuadraticEquation(1.0f, 0.0, +1.0);
    EXPECT_EQ(std::vector<float>({}), quadratic.getRoots());
}

TEST(QuadraticEquation, all_coeficients)
{
    auto quadratic = QuadraticEquation(3.0f, -5.0, -7.0);
    EXPECT_TRUE(quadratic.hasRoot());
    EXPECT_EQ(2u, quadratic.getNumberOfRoots());
    const auto roots = quadratic.getRoots();
    EXPECT_EQ(2u, roots.size());
    EXPECT_FLOAT_EQ(2.5733845f, roots[0]);
    EXPECT_FLOAT_EQ(-0.90671772f, roots[1]);
}