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
