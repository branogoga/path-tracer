#pragma once

#include "point.h"

#include <cstddef>

namespace geometry {
    class Matrix
    {
    public:
        static const size_t    XX = 0;
        static const size_t    XY = 1;
        static const size_t    XZ = 2;
        static const size_t    XW = 3;
        static const size_t    YX = 4;
        static const size_t    YY = 5;
        static const size_t    YZ = 6;
        static const size_t    YW = 7;
        static const size_t    ZX = 8;
        static const size_t    ZY = 9;
        static const size_t    ZZ = 10;
        static const size_t    ZW = 11;
        static const size_t    WX = 12;
        static const size_t    WY = 13;
        static const size_t    WZ = 14;
        static const size_t    WW = 15;

        Matrix();
        Matrix(const Point& p1, const Point& p2, const Point& p3, const Point& o);
        Matrix(const std::array<float, 16>& data);

        float* operator[](size_t i);
        const float* operator[](size_t i) const;
        float& operator()(size_t index);
        const float& operator()(size_t index) const;
        float& operator()(size_t row, size_t col);
        const float& operator()(size_t row, size_t col) const;

        Matrix inverse() const;
        Matrix transpose() const;
    private:
        void initRows();

        std::array<float*, 4> rows;
        std::array<float, 16> data;
    };

    Vector operator*(const Matrix& m, const Vector& v);
    Point operator*(const Matrix& m, const Point& p);
    Matrix operator*(const Matrix& m1, const Matrix& m2);

    bool isEqual(const Matrix& m1, const Matrix& m2, const float precision = 1E-06);

    Matrix inverse(const Matrix& m);
    Matrix transpose(const Matrix& m);

    // TODO: ortographicProjection, perspectiveProjection
    // TODO: gramSchmidtOrthogonalization
    // TODO: determinant
    // TODO: isOrthogonal
    // TODO: isRightHanded
    // TODO: trace
    // TODO: ZeroMatrix, IdentityMatrix

    Matrix translation(float x, float y, float z);
    Matrix scaling(float x, float y, float z);
    Matrix rotationX(float angleInRadians);
    Matrix rotationY(float angleInRadians);
    Matrix rotationZ(float angleInRadians);
    Matrix orthographicProjection(float left, float right, float top, float bottom, float N, float F);
    Matrix perspectiveTransformation(float N, float F);
} //namespace geometry