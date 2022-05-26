#include "axis.h"
#include "matrix.h"
#include "vector.h"

#include <math.h>

namespace geometry
{
    Matrix::Matrix()
        : data({
           1.0f, 0.0f, 0.0f, 0.0f,
           0.0f, 1.0f, 0.0f, 0.0f,
           0.0f, 0.0f, 1.0f, 0.0f,
           0.0f, 0.0f, 0.0f, 1.0f
       })
    {
        initRows();
    }

    Matrix::Matrix(const Point& p1, const Point& p2, const Point& p3, const Point& o)
        : data({
           p1[Axis::X], p2[Axis::X], p3[Axis::X], o[Axis::X],
           p1[Axis::Y], p2[Axis::Y], p3[Axis::Y], o[Axis::Y],
           p1[Axis::Z], p2[Axis::Z], p3[Axis::Z], o[Axis::Z],
           0.0f, 0.0f, 0.0f, 1.0f
       })
    {
        initRows();
    }

    Matrix::Matrix(const std::array<float, 16>& data): data(data)
    {
        initRows();
    }


    void Matrix::initRows()
    {
        rows[Axis::X] = &(data[XX]);
        rows[Axis::Y] = &(data[YX]);
        rows[Axis::Z] = &(data[ZX]);
        rows[Axis::W] = &(data[WX]);
    }

    float* Matrix::operator[](size_t i)
    {
        return rows[i];
    }

    const float* Matrix::operator[](size_t i) const
    {
        return rows[i];
    }

    float& Matrix::operator()(size_t row, size_t col)
    {
        return (*this)[row][col];
    }

    const float& Matrix::operator()(size_t row, size_t col) const
    {
        return (*this)[row][col];
    }

    float& Matrix::operator()(size_t index)
    {
        return data[index];
    }

    const float& Matrix::operator()(size_t index) const
    {
        return data[index];
    }

    // (m11 m12 m13 m14)   (v1)    (v1*m11 + v2*m12 + v3*m13 + 0*m14)
    // (m21 m22 m23 m24) * (v2) =  (v1*m21 + v2*m22 + v3*m23 + 0*m24)
    // (m31 m32 m33 m34)   (v3)    (v1*m31 + v2*m32 + v3*m33 + 0*m34)
    // ( 0   0   0   1)    (0 )    (                0               )
    Vector operator*(const Matrix& m, const Vector& v)
    {
        return Vector({
            v[Axis::X]*m[Axis::X][Axis::X] + v[Axis::Y]*m[Axis::X][Axis::Y] + v[Axis::Z]*m[Axis::X][Axis::Z],
            v[Axis::X]*m[Axis::Y][Axis::X] + v[Axis::Y]*m[Axis::Y][Axis::Y] + v[Axis::Z]*m[Axis::Y][Axis::Z],
            v[Axis::X]*m[Axis::Z][Axis::X] + v[Axis::Y]*m[Axis::Z][Axis::Y] + v[Axis::Z]*m[Axis::Z][Axis::Z]
        });
    }

    // (m11 m12 m13 m14)   (p1)    (p1*m11 + p2*m12 + p3*m13 + 1*m14)
    // (m21 m22 m23 m24) * (p2) =  (p1*m21 + p2*m22 + p3*m23 + 1*m24)
    // (m31 m32 m33 m34)   (p3)    (p1*m31 + p2*m32 + p3*m33 + 1*m34)
    // ( 0   0   0   1)    (1 )    (                1               )
    Point operator*(const Matrix& m, const Point& p) {
        return Point({
            p[Axis::X]*m[Axis::X][Axis::X] + p[Axis::Y]*m[Axis::X][Axis::Y] + p[Axis::Z]*m[Axis::X][Axis::Z] + m[Axis::X][Axis::W],
            p[Axis::X]*m[Axis::Y][Axis::X] + p[Axis::Y]*m[Axis::Y][Axis::Y] + p[Axis::Z]*m[Axis::Y][Axis::Z] + m[Axis::Y][Axis::W],
            p[Axis::X]*m[Axis::Z][Axis::X] + p[Axis::Y]*m[Axis::Z][Axis::Y] + p[Axis::Z]*m[Axis::Z][Axis::Z] + m[Axis::Z][Axis::W]
        });
    }

    Matrix operator*(const Matrix& m1, const Matrix& m2)
    {
        Matrix result;
        for(size_t row = 0; row < 4; ++row)
        {
            for(size_t column = 0; column < 4; ++column)
            {
                float value = 0.0f;
                for(size_t k = 0; k < 4; ++k)
                {
                    value += m1[row][k]*m2[k][column];
                }
                result[row][column] = value;
            }
        }
        return result;
    }

    Matrix translation(float x, float y, float z)
    {
        return Matrix(Point({1.0, 0.0, 0.0}), Point({0.0, 1.0, 0.0}), Point({0.0, 0.0, 1.0}), Point({x, y, z}));
    }

    Matrix scaling(float x, float y, float z)
    {
        return Matrix(Point({x, 0.0, 0.0}), Point({0.0, y, 0.0}), Point({0.0, 0.0, z}), Point({0.0, 0.0, 0.0}));
    }

    Matrix rotationX(float angleInRadians)
    {
        auto c = cos(angleInRadians);
        auto s = sin(angleInRadians);

        return Matrix({
            1.0f, 0.0, 0.0, 0.0,
            0.0, c, -s, 0.0,
            0.0, s, c, 0.0,
            0.0, 0.0, 0.0, 1
        });
    }

    Matrix rotationY(float angleInRadians)
    {
        auto c = cos(angleInRadians);
        auto s = sin(angleInRadians);


        return Matrix({
            c, 0.0, s, 0.0,
            0.0, 1.0f, 0.0, 0.0,
            -s, 0.0, c, 0.0,
            0.0, 0.0, 0.0, 1
        });
    }

    Matrix rotationZ(float angleInRadians)
    {
        auto c = cos(angleInRadians);
        auto s = sin(angleInRadians);

        return Matrix({
            c, -s, 0.0, 0.0,
            s, c, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1
        });
    }
    

} // namespace geometry