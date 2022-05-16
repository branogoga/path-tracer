#include "vector.h"

#include "gtest/gtest.h"

#include <cmath>

using namespace geometry;

void EXPECT_VECTOR_EQ(Vector expected, Vector result) {
    EXPECT_EQ(expected.dimension(), result.dimension());
    for(size_t i = 0; i < result.dimension(); ++i) {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}

TEST(Vector, component_assignment)
{
    auto v = Vector();
    v[Axis::X] = 1.0f;
    EXPECT_EQ(1.0f, v[Axis::X]);

    v[Axis::Y] = 2.0f;
    EXPECT_EQ(2.0f, v[Axis::Y]);

    v[Axis::Z] = 5.0f;
    EXPECT_EQ(5.0f, v[Axis::Z]);
}

TEST(Vector, assignment)
{
    auto v1 = Vector({1.0f, 2.0f, 3.0f});
    auto v2 = v1;
    v1[Axis::X] = 7.0f;
    EXPECT_EQ(1.0f, v2[Axis::X]);
    EXPECT_EQ(2.0f, v2[Axis::Y]);
    EXPECT_EQ(3.0f, v2[Axis::Z]);
}

TEST(Vector, addition)
{
    auto v1 = Vector({1.0f, 2.0f, 3.0f});
    auto v2 = Vector({7.0f, 5.0f, 9.0f});
    auto v3 = v1 + v2;

    EXPECT_EQ(8.0f, v3[Axis::X]);
    EXPECT_EQ(7.0f, v3[Axis::Y]);
    EXPECT_EQ(12.0f, v3[Axis::Z]);
}

TEST(Vector, scaling)
{
    auto v1 = Vector({1.0f, 2.0f, 3.0f});
    auto v2 = 10 * v1;

    EXPECT_EQ(10.0f, v2[Axis::X]);
    EXPECT_EQ(20.0f, v2[Axis::Y]);
    EXPECT_EQ(30.0f, v2[Axis::Z]);

    auto v3 = v1 * 10;

    EXPECT_EQ(10.0f, v3[Axis::X]);
    EXPECT_EQ(20.0f, v3[Axis::Y]);
    EXPECT_EQ(30.0f, v3[Axis::Z]);
}

TEST(Vector, length)
{
    EXPECT_EQ(0.0f, length(Vector({0.0f, 0.0f, 0.0f})));
    EXPECT_EQ(1.0f, length(Vector({1.0f, 0.0f, 0.0f})));
    EXPECT_EQ(1.0f, length(Vector({0.0f, 1.0f, 0.0f})));
    EXPECT_EQ(1.0f, length(Vector({0.0f, 0.0f, 1.0f})));
    EXPECT_EQ(7.0f, length(Vector({7.0f, 0.0f, 0.0f})));
    EXPECT_EQ(1.0f, length(Vector({-1.0f, 0.0f, 0.0f})));
    EXPECT_FLOAT_EQ(sqrt(14.0f), length(Vector({1.0f, 2.0f, 3.0f})));
}

TEST(Vector, dot)
{
    EXPECT_EQ(0.0f, dot(Vector({0.0f, 0.0f, 0.0f}), Vector({1.0, 2.0, 3.0})));
    EXPECT_EQ(1.0f, dot(Vector({1.0f, 0.0f, 0.0f}), Vector({1.0f, 0.0f, 0.0f})));
    EXPECT_EQ(0.0f, dot(Vector({1.0f, 0.0f, 0.0f}), Vector({0.0f, 1.0f, 0.0f})));
    EXPECT_EQ(0.0f, dot(Vector({1.0f, 0.0f, 0.0f}), Vector({0.0f, 3.0f, 2.0f})));
    EXPECT_EQ(20.0f, dot(Vector({1.0f, 3.0f, 5.0f}), Vector({2.0f, -4.0f, 6.0f})));
}

//TEST(Vector, normalize_zero_vector) {
//    // TODO: Check division by zero!
//    EXPECT_THROW(normalize(Vector({0.0f, 0.0f, 0.0f})), std::invalid_argument);
//}

TEST(Vector, normalize_unit_vector) {
    EXPECT_VECTOR_EQ(Vector({1.0f, 0.0f, 0.0f}), normalize(Vector({1.0f, 0.0f, 0.0f})));
}

TEST(Vector, normalize_scaled_axis_vector) {
    EXPECT_VECTOR_EQ(Vector({1.0f, 0.0f, 0.0f}), normalize(Vector({7.0f, 0.0f, 0.0f})));
}

TEST(Vector, normalize_negative_axis_vector) {
    EXPECT_VECTOR_EQ(Vector({-1.0f, 0.0f, 0.0f}), normalize(Vector({-1.0f, 0.0f, 0.0f})));
}

TEST(Vector, normalize_complex_vector) {
    EXPECT_VECTOR_EQ(Vector({1.0f/sqrtf(14.0f), 2.0f/sqrtf(14.0f), 3.0f/sqrtf(14.0f)}), normalize(Vector({1.0f, 2.0f, 3.0f})));
}

TEST(Vector, cross_axis_x_y) {
    EXPECT_VECTOR_EQ(
    Vector({0.0f, 0.0f, 1.0f}),
    cross(Vector({1.0f, 0.0f, 0.0f}), Vector({0.0f, 1.0f, 0.0f}))
    );
}

TEST(Vector, cross_axis_y_x) {
    EXPECT_VECTOR_EQ(
            Vector({0.0f, 0.0f, -1.0f}),
            cross(Vector({0.0f, 1.0f, 0.0f}), Vector({1.0f, 0.0f, 0.0f}))
    );
}

TEST(Vector, angle) {
    EXPECT_FLOAT_EQ(0.0, angle(Vector({1.0f, 2.0f, 3.0f}), Vector({1.0f, 2.0f, 3.0f})));
    EXPECT_FLOAT_EQ(M_PI / 2, angle(Vector({1.0f, 0.0f, 0.0f}), Vector({0.0f, 1.0f, 0.0f})));
    EXPECT_FLOAT_EQ(M_PI / 2, angle(Vector({1.0f, 0.0f, 0.0f}), Vector({0.0f, -1.0f, 0.0f})));
    EXPECT_FLOAT_EQ(M_PI, angle(Vector({1.0f, 0.0f, 0.0f}), Vector({-1.0f, 0.0f, 0.0f})));
}
