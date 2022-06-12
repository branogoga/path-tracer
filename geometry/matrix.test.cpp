#include "axis.h"
#include "matrix.h"
#include "vector.h"

#include "gtest/gtest.h"

#include "math.h"

using namespace geometry;

TEST(Matrix, default_constructor) {
    auto m = Matrix();
    EXPECT_FLOAT_EQ(1.0, m[Axis::X][Axis::X]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::X][Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::X][Axis::Z]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::X][Axis::W]);

    EXPECT_FLOAT_EQ(0.0, m[Axis::Y][Axis::X]);
    EXPECT_FLOAT_EQ(1.0, m[Axis::Y][Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::Y][Axis::Z]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::Y][Axis::W]);

    EXPECT_FLOAT_EQ(0.0, m[Axis::Z][Axis::X]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::Z][Axis::Y]);
    EXPECT_FLOAT_EQ(1.0, m[Axis::Z][Axis::Z]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::Z][Axis::W]);

    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::X]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::Z]);
    EXPECT_FLOAT_EQ(1.0, m[Axis::W][Axis::W]);
}

TEST(Matrix, create_from_points) {
    auto m = Matrix(Point({1.0f, 2.0f, 3.0f}), Point({4.0f, 5.0f, 6.0f}), Point({7.0f, 8.0f, 9.0f}), Point({10.0f, 11.0f, 12.0f}));

    // [][]
    EXPECT_FLOAT_EQ(1.0, m[Axis::X][Axis::X]);
    EXPECT_FLOAT_EQ(4.0, m[Axis::X][Axis::Y]);
    EXPECT_FLOAT_EQ(7.0, m[Axis::X][Axis::Z]);
    EXPECT_FLOAT_EQ(10.0, m[Axis::X][Axis::W]);

    EXPECT_FLOAT_EQ(2.0, m[Axis::Y][Axis::X]);
    EXPECT_FLOAT_EQ(5.0, m[Axis::Y][Axis::Y]);
    EXPECT_FLOAT_EQ(8.0, m[Axis::Y][Axis::Z]);
    EXPECT_FLOAT_EQ(11.0, m[Axis::Y][Axis::W]);

    EXPECT_FLOAT_EQ(3.0, m[Axis::Z][Axis::X]);
    EXPECT_FLOAT_EQ(6.0, m[Axis::Z][Axis::Y]);
    EXPECT_FLOAT_EQ(9.0, m[Axis::Z][Axis::Z]);
    EXPECT_FLOAT_EQ(12.0, m[Axis::Z][Axis::W]);

    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::X]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::Y]);
    EXPECT_FLOAT_EQ(0.0, m[Axis::W][Axis::Z]);
    EXPECT_FLOAT_EQ(1.0, m[Axis::W][Axis::W]);

    // (row, col)
    EXPECT_FLOAT_EQ(1.0, m(Axis::X,Axis::X));
    EXPECT_FLOAT_EQ(4.0, m(Axis::X,Axis::Y));
    EXPECT_FLOAT_EQ(7.0, m(Axis::X,Axis::Z));
    EXPECT_FLOAT_EQ(10.0, m(Axis::X,Axis::W));

    EXPECT_FLOAT_EQ(2.0, m(Axis::Y,Axis::X));
    EXPECT_FLOAT_EQ(5.0, m(Axis::Y,Axis::Y));
    EXPECT_FLOAT_EQ(8.0, m(Axis::Y,Axis::Z));
    EXPECT_FLOAT_EQ(11.0, m(Axis::Y,Axis::W));

    EXPECT_FLOAT_EQ(3.0, m(Axis::Z,Axis::X));
    EXPECT_FLOAT_EQ(6.0, m(Axis::Z,Axis::Y));
    EXPECT_FLOAT_EQ(9.0, m(Axis::Z,Axis::Z));
    EXPECT_FLOAT_EQ(12.0, m(Axis::Z,Axis::W));

    EXPECT_FLOAT_EQ(0.0, m(Axis::W,Axis::X));
    EXPECT_FLOAT_EQ(0.0, m(Axis::W,Axis::Y));
    EXPECT_FLOAT_EQ(0.0, m(Axis::W,Axis::Z));
    EXPECT_FLOAT_EQ(1.0, m(Axis::W,Axis::W));

    // (index)
    EXPECT_FLOAT_EQ(1.0, m(Matrix::XX));
    EXPECT_FLOAT_EQ(4.0, m(Matrix::XY));
    EXPECT_FLOAT_EQ(7.0, m(Matrix::XZ));
    EXPECT_FLOAT_EQ(10.0, m(Matrix::XW));

    EXPECT_FLOAT_EQ(2.0, m(Matrix::YX));
    EXPECT_FLOAT_EQ(5.0, m(Matrix::YY));
    EXPECT_FLOAT_EQ(8.0, m(Matrix::YZ));
    EXPECT_FLOAT_EQ(11.0, m(Matrix::YW));

    EXPECT_FLOAT_EQ(3.0, m(Matrix::ZX));
    EXPECT_FLOAT_EQ(6.0, m(Matrix::ZY));
    EXPECT_FLOAT_EQ(9.0, m(Matrix::ZZ));
    EXPECT_FLOAT_EQ(12.0, m(Matrix::ZW));

    EXPECT_FLOAT_EQ(0.0, m(Matrix::WX));
    EXPECT_FLOAT_EQ(0.0, m(Matrix::WY));
    EXPECT_FLOAT_EQ(0.0, m(Matrix::WZ));
    EXPECT_FLOAT_EQ(1.0, m(Matrix::WW));

    for(size_t row = 0; row < 4; ++row)
    {
        for(size_t col = 0; col < 4; ++col)
        {
            EXPECT_FLOAT_EQ(m[row][col], m(row, col));
            EXPECT_FLOAT_EQ(m[row][col], m(4*row+col));
        }
    }
}

TEST(Matrix, multiply_matrix_vector) {
    auto m = Matrix(
    Point({1.0f, 2.0f, 3.0f}),
    Point({4.0f, 5.0f, 6.0f}),
    Point({7.0f, 8.0f, 9.0f}),
     Point({10.0f, 11.0f, 12.0f})
     );

    auto x = m * Vector({1.0f, 0.0f, 0.0f});
    EXPECT_FLOAT_EQ(1.0f, x[Axis::X]);
    EXPECT_FLOAT_EQ(2.0f, x[Axis::Y]);
    EXPECT_FLOAT_EQ(3.0f, x[Axis::Z]);


    auto y = m * Vector({0.0f, 1.0f, 0.0f});
    EXPECT_FLOAT_EQ(4.0f, y[Axis::X]);
    EXPECT_FLOAT_EQ(5.0f, y[Axis::Y]);
    EXPECT_FLOAT_EQ(6.0f, y[Axis::Z]);

    auto z = m * Vector({0.0f, 0.0f, 1.0f});
    EXPECT_FLOAT_EQ(7.0f, z[Axis::X]);
    EXPECT_FLOAT_EQ(8.0f, z[Axis::Y]);
    EXPECT_FLOAT_EQ(9.0f, z[Axis::Z]);
}

TEST(Matrix, multiply_matrix_point) {
    auto m = Matrix(
            Point({1.0f, 2.0f, 3.0f}),
            Point({4.0f, 5.0f, 6.0f}),
            Point({7.0f, 8.0f, 9.0f}),
            Point({10.0f, 11.0f, 12.0f})
    );

    auto o = m * Point({0.0f, 0.0f, 0.0f});
    EXPECT_FLOAT_EQ(10.0f, o[Axis::X]);
    EXPECT_FLOAT_EQ(11.0f, o[Axis::Y]);
    EXPECT_FLOAT_EQ(12.0f, o[Axis::Z]);


    auto x = m * Point({1.0f, 0.0f, 0.0f});
    EXPECT_FLOAT_EQ(11.0f, x[Axis::X]);
    EXPECT_FLOAT_EQ(13.0f, x[Axis::Y]);
    EXPECT_FLOAT_EQ(15.0f, x[Axis::Z]);


    auto y = m * Point({0.0f, 1.0f, 0.0f});
    EXPECT_FLOAT_EQ(14.0f, y[Axis::X]);
    EXPECT_FLOAT_EQ(16.0f, y[Axis::Y]);
    EXPECT_FLOAT_EQ(18.0f, y[Axis::Z]);

    auto z = m * Point({0.0f, 0.0f, 1.0f});
    EXPECT_FLOAT_EQ(17.0f, z[Axis::X]);
    EXPECT_FLOAT_EQ(19.0f, z[Axis::Y]);
    EXPECT_FLOAT_EQ(21.0f, z[Axis::Z]);
}

TEST(Matrix, compose_matrix) {
    auto s = scaling(1.0f, 2.0f, 3.0f);
    auto t = translation(13.0f, 25.0f, 37.0f);
    auto st =s*t;
    auto ts =t*s;
    auto o = Point({0.0f, 0.0f, 0.0f});

    auto sto = st*o;
    EXPECT_FLOAT_EQ(13.0f, sto[Axis::X]);
    EXPECT_FLOAT_EQ(50.0f, sto[Axis::Y]);
    EXPECT_FLOAT_EQ(111.0f, sto[Axis::Z]);

    auto tso = ts*o;
    EXPECT_FLOAT_EQ(13.0f, tso[Axis::X]);
    EXPECT_FLOAT_EQ(25.0f, tso[Axis::Y]);
    EXPECT_FLOAT_EQ(37.0f, tso[Axis::Z]);
}

TEST(Matrix, rotationX) {
    auto rx = rotationX(M_PI/2);

    auto o = rx * Point({0.0, 0.0, 0.0});
    EXPECT_FLOAT_EQ(0.0f, o[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Z]);

    auto x = rx * Point({1.0, 0.0, 0.0});
    EXPECT_FLOAT_EQ(1.0f, x[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, x[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, x[Axis::Z]);

    auto y = rx * Point({0.0, 1.0, 0.0});
    EXPECT_FLOAT_EQ(0.0f, y[Axis::X]);
    EXPECT_NEAR(0.0f, y[Axis::Y], 1E-07);
    EXPECT_FLOAT_EQ(1.0f, y[Axis::Z]);

    auto z = rx * Point({0.0, 0.0, 1.0});
    EXPECT_FLOAT_EQ(0.0f, z[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, z[Axis::Y]);
    EXPECT_NEAR(0.0f, z[Axis::Z], 1E-07);
}

TEST(Matrix, rotationY) {
    auto ry = rotationY(M_PI/2);

    auto o = ry * Point({0.0, 0.0, 0.0});
    EXPECT_FLOAT_EQ(0.0f, o[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Z]);

    auto x = ry * Point({1.0, 0.0, 0.0});
    EXPECT_NEAR(0.0f, x[Axis::X], 1E-07);
    EXPECT_FLOAT_EQ(0.0f, x[Axis::Y]);
    EXPECT_FLOAT_EQ(-1.0f, x[Axis::Z]);

    auto y = ry * Point({0.0, 1.0, 0.0});
    EXPECT_FLOAT_EQ(0.0f, y[Axis::X]);
    EXPECT_FLOAT_EQ(1.0f, y[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, y[Axis::Z]);

    auto z = ry * Point({0.0, 0.0, 1.0});
    EXPECT_FLOAT_EQ(1.0f, z[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, z[Axis::Y]);
    EXPECT_NEAR(0.0f, z[Axis::Z], 1E-07);
}

TEST(Matrix, rotationZ) {
    auto rz = rotationZ(M_PI/2);

    auto o = rz * Point({0.0, 0.0, 0.0});
    EXPECT_FLOAT_EQ(0.0f, o[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, o[Axis::Z]);

    auto x = rz * Point({1.0, 0.0, 0.0});
    EXPECT_NEAR(0.0f, x[Axis::X], 1E-07);
    EXPECT_FLOAT_EQ(1.0f, x[Axis::Y]);
    EXPECT_FLOAT_EQ(0.0f, x[Axis::Z]);

    auto y = rz * Point({0.0, 1.0, 0.0});
    EXPECT_FLOAT_EQ(-1.0f, y[Axis::X]);
    EXPECT_NEAR(0.0f, y[Axis::Y], 1E-07);
    EXPECT_FLOAT_EQ(0.0f, y[Axis::Z]);

    auto z = rz * Point({0.0, 0.0, 1.0});
    EXPECT_FLOAT_EQ(0.0f, z[Axis::X]);
    EXPECT_FLOAT_EQ(0.0f, z[Axis::Y]);
    EXPECT_FLOAT_EQ(1.0f, z[Axis::Z]);
}

TEST(Matrix, inverseTranslation)
{
    EXPECT_TRUE(isEqual(translation(-10.0, -20.0, -30.0), inverse(translation(10.0, 20.0, 30.0))));
}

TEST(Matrix, inverseScaling)
{
    EXPECT_TRUE(isEqual(scaling(1/10.0, 1/20.0, 1/30.0), inverse(scaling(10.0, 20.0, 30.0))));
}

TEST(Matrix, inverseRotationX)
{
    EXPECT_TRUE(isEqual(rotationX(M_PI/2), inverse(rotationX(-M_PI/2))));
}

TEST(Matrix, inverseRotationY)
{
    EXPECT_TRUE(isEqual(rotationY(M_PI/2), inverse(rotationY(-M_PI/2))));
}

TEST(Matrix, inverseRotationZ)
{
    EXPECT_TRUE(isEqual(rotationZ(M_PI/2), inverse(rotationZ(-M_PI/2))));
}

TEST(Matrix, transpose)
{
    auto m = Matrix(
            Point({1.0f, 2.0f, 3.0f}),
            Point({4.0f, 5.0f, 6.0f}),
            Point({7.0f, 8.0f, 9.0f}),
            Point({10.0f, 11.0f, 12.0f})
    );

    auto transposed = transpose(m);

    for(size_t row = 0; row < 4; ++row)
    {
        for(size_t col = 0; col < 4; ++col)
        {
            EXPECT_FLOAT_EQ(m[row][col], transposed[col][row]);
        }
    }
}

TEST(Matrix, orthographicProjectionProjectsPointToCanonicalVolumeIdentity)
{
    float left = -1.0f;
    float right = +1.0f;
    float top = +1.0f;
    float bottom = -1.0f;
    float N = -1.0f;
    float F = 1.0f;

    auto worldToNormalizedScreenCoordinatesMatrix = geometry::orthographicProjection(left, right, top, bottom, N, F);

    auto near_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, N});
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::Y]);
    EXPECT_FLOAT_EQ(+1.0f, near_left_bottom[Axis::Z]);

    auto near_center = worldToNormalizedScreenCoordinatesMatrix * Point({0.0, 0.0, N});
    EXPECT_NEAR(0.0f, near_center[Axis::X], 1E-06);
    EXPECT_NEAR(0.0f, near_center[Axis::Y], 1E-06);
    EXPECT_FLOAT_EQ(+1.0f, near_center[Axis::Z]);

    auto near_right_top = worldToNormalizedScreenCoordinatesMatrix * Point({right, top, N});
    EXPECT_NEAR(+1.0f, near_right_top[Axis::X], 1E-06);
    EXPECT_NEAR(+1.0f, near_right_top[Axis::Y], 1E-06);
    EXPECT_FLOAT_EQ(+1.0f, near_right_top[Axis::Z]);

    auto far_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, F});
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::Y]);
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::Z]);
}

TEST(Matrix, projectsPointToCanonicalVolumeScaling)
{
    float left = -2.0f;
    float right = +2.0f;
    float top = +3.0f;
    float bottom = -3.0f;
    float N = -4.0f;
    float F = 4.0f;

    auto worldToNormalizedScreenCoordinatesMatrix = geometry::orthographicProjection(left, right, top, bottom, N, F);

    auto near_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, N});
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::Y]);
    EXPECT_FLOAT_EQ(+1.0f, near_left_bottom[Axis::Z]);

    auto near_center = worldToNormalizedScreenCoordinatesMatrix * Point({0.0, 0.0, N});
    EXPECT_NEAR(0.0f, near_center[Axis::X], 1E-06);
    EXPECT_NEAR(0.0f, near_center[Axis::Y], 1E-06);
    EXPECT_FLOAT_EQ(+1.0f, near_center[Axis::Z]);

    auto near_right_top = worldToNormalizedScreenCoordinatesMatrix * Point({right, top, N});
    EXPECT_NEAR(+1.0f, near_right_top[Axis::X], 1E-06);
    EXPECT_NEAR(+1.0f, near_right_top[Axis::Y], 1E-06);
    EXPECT_FLOAT_EQ(+1.0f, near_right_top[Axis::Z]);

    auto far_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, F});
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::Y]);
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::Z]);
}

TEST(Matrix, projectsPointToCanonicalVolumeTranslation)
{
    float left =-3.0f;
    float right = +5.0f;
    float top = +7.0f;
    float bottom = +3.0f;
    float N = -10.0f;
    float F = -20.0f;

    auto worldToNormalizedScreenCoordinatesMatrix = geometry::orthographicProjection(left, right, top, bottom, N, F);

    auto near_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, N});
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::Y]);
    //EXPECT_FLOAT_EQ(-1.0f, near_left_bottom[Axis::Z]);

    auto near_center = worldToNormalizedScreenCoordinatesMatrix * Point({1.0, 5.0, (N+F)/2});
    EXPECT_NEAR(0.0f, near_center[Axis::X], 1E-06);
    EXPECT_NEAR(0.0f, near_center[Axis::Y], 1E-06);
    EXPECT_FLOAT_EQ(0.0f, near_center[Axis::Z]);

    auto near_right_top = worldToNormalizedScreenCoordinatesMatrix * Point({right, top, N});
    EXPECT_NEAR(+1.0f, near_right_top[Axis::X], 1E-06);
    EXPECT_NEAR(+1.0f, near_right_top[Axis::Y], 1E-06);
    //EXPECT_FLOAT_EQ(-1.0f, near_right_top[Axis::Z]);

    auto far_left_bottom = worldToNormalizedScreenCoordinatesMatrix * Point({left, bottom, F});
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(-1.0f, far_left_bottom[Axis::Y]);
    //EXPECT_FLOAT_EQ(+1.0f, far_left_bottom[Axis::Z]);
}

TEST(Matrix, projectsCanonicalVolumeTo) {
    float left = -3.0f;
    float right = +5.0f;
    float top = +7.0f;
    float bottom = +3.0f;
    float N = -10.0f;
    float F = -20.0f;

    auto normalizedScreenToWorldCoordinatesMatrix = geometry::inverse(geometry::orthographicProjection(left, right, top, bottom, N, F));

    auto near_left_bottom = normalizedScreenToWorldCoordinatesMatrix * Point({-1.0, -1.0, -1.0});
    EXPECT_FLOAT_EQ(left, near_left_bottom[Axis::X]);
    EXPECT_FLOAT_EQ(bottom, near_left_bottom[Axis::Y]);
    //EXPECT_FLOAT_EQ(N, near_left_bottom[Axis::Z]);

    auto far_top_right = normalizedScreenToWorldCoordinatesMatrix * Point({+1.0, +1.0, +1.0});
    EXPECT_FLOAT_EQ(right, far_top_right[Axis::X]);
    EXPECT_FLOAT_EQ(top, far_top_right[Axis::Y]);
    //EXPECT_FLOAT_EQ(F, far_top_right[Axis::Z]);
}

TEST(Matrix, perspectiveTransformation)
{
    float N = 1;
    float F = 100;

    // a = -101/99
    // b = -200/99
    // pseudodepth = (101*Pz+200)/(99*Pz)
    auto m = geometry::perspectiveTransformation(N, F);

    auto near = m * Point({0.0, 0.0, -1.0});
    EXPECT_NEAR(-1.0f, near[Axis::Z], 1E-06);

    auto f1 = m * Point({0.0, 0.0, -97});
    EXPECT_FLOAT_EQ(+.9993752f, f1[Axis::Z]);

    auto f2 = m * Point({0.0, 0.0, -98});
    EXPECT_FLOAT_EQ(+.9995877f, f2[Axis::Z]);

    auto f3 = m * Point({0.0, 0.0, -99});
    EXPECT_FLOAT_EQ(+.9997959, f3[Axis::Z]);

    auto f4 = m * Point({0.0, 0.0, -F});
    EXPECT_FLOAT_EQ(+1.0f, f4[Axis::Z]);
}
