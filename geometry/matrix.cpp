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

    Matrix Matrix::inverse() const
    {
        std::array<float, 16> inv;

        inv[0] = data[5]  * data[10] * data[15] -
                 data[5]  * data[11] * data[14] -
                 data[9]  * data[6]  * data[15] +
                 data[9]  * data[7]  * data[14] +
                 data[13] * data[6]  * data[11] -
                 data[13] * data[7]  * data[10];

        inv[4] = -data[4]  * data[10] * data[15] +
                 data[4]  * data[11] * data[14] +
                 data[8]  * data[6]  * data[15] -
                 data[8]  * data[7]  * data[14] -
                 data[12] * data[6]  * data[11] +
                 data[12] * data[7]  * data[10];

        inv[8] = data[4]  * data[9] * data[15] -
                 data[4]  * data[11] * data[13] -
                 data[8]  * data[5] * data[15] +
                 data[8]  * data[7] * data[13] +
                 data[12] * data[5] * data[11] -
                 data[12] * data[7] * data[9];

        inv[12] = -data[4]  * data[9] * data[14] +
                  data[4]  * data[10] * data[13] +
                  data[8]  * data[5] * data[14] -
                  data[8]  * data[6] * data[13] -
                  data[12] * data[5] * data[10] +
                  data[12] * data[6] * data[9];

        inv[1] = -data[1]  * data[10] * data[15] +
                 data[1]  * data[11] * data[14] +
                 data[9]  * data[2] * data[15] -
                 data[9]  * data[3] * data[14] -
                 data[13] * data[2] * data[11] +
                 data[13] * data[3] * data[10];

        inv[5] = data[0]  * data[10] * data[15] -
                 data[0]  * data[11] * data[14] -
                 data[8]  * data[2] * data[15] +
                 data[8]  * data[3] * data[14] +
                 data[12] * data[2] * data[11] -
                 data[12] * data[3] * data[10];

        inv[9] = -data[0]  * data[9] * data[15] +
                 data[0]  * data[11] * data[13] +
                 data[8]  * data[1] * data[15] -
                 data[8]  * data[3] * data[13] -
                 data[12] * data[1] * data[11] +
                 data[12] * data[3] * data[9];

        inv[13] = data[0]  * data[9] * data[14] -
                  data[0]  * data[10] * data[13] -
                  data[8]  * data[1] * data[14] +
                  data[8]  * data[2] * data[13] +
                  data[12] * data[1] * data[10] -
                  data[12] * data[2] * data[9];

        inv[2] = data[1]  * data[6] * data[15] -
                 data[1]  * data[7] * data[14] -
                 data[5]  * data[2] * data[15] +
                 data[5]  * data[3] * data[14] +
                 data[13] * data[2] * data[7] -
                 data[13] * data[3] * data[6];

        inv[6] = -data[0]  * data[6] * data[15] +
                 data[0]  * data[7] * data[14] +
                 data[4]  * data[2] * data[15] -
                 data[4]  * data[3] * data[14] -
                 data[12] * data[2] * data[7] +
                 data[12] * data[3] * data[6];

        inv[10] = data[0]  * data[5] * data[15] -
                  data[0]  * data[7] * data[13] -
                  data[4]  * data[1] * data[15] +
                  data[4]  * data[3] * data[13] +
                  data[12] * data[1] * data[7] -
                  data[12] * data[3] * data[5];

        inv[14] = -data[0]  * data[5] * data[14] +
                  data[0]  * data[6] * data[13] +
                  data[4]  * data[1] * data[14] -
                  data[4]  * data[2] * data[13] -
                  data[12] * data[1] * data[6] +
                  data[12] * data[2] * data[5];

        inv[3] = -data[1] * data[6] * data[11] +
                 data[1] * data[7] * data[10] +
                 data[5] * data[2] * data[11] -
                 data[5] * data[3] * data[10] -
                 data[9] * data[2] * data[7] +
                 data[9] * data[3] * data[6];

        inv[7] = data[0] * data[6] * data[11] -
                 data[0] * data[7] * data[10] -
                 data[4] * data[2] * data[11] +
                 data[4] * data[3] * data[10] +
                 data[8] * data[2] * data[7] -
                 data[8] * data[3] * data[6];

        inv[11] = -data[0] * data[5] * data[11] +
                  data[0] * data[7] * data[9] +
                  data[4] * data[1] * data[11] -
                  data[4] * data[3] * data[9] -
                  data[8] * data[1] * data[7] +
                  data[8] * data[3] * data[5];

        inv[15] = data[0] * data[5] * data[10] -
                  data[0] * data[6] * data[9] -
                  data[4] * data[1] * data[10] +
                  data[4] * data[2] * data[9] +
                  data[8] * data[1] * data[6] -
                  data[8] * data[2] * data[5];

        float det = data[0] * inv[0] + data[1] * inv[4] + data[2] * inv[8] + data[3] * inv[12];

        if (det == 0) {
            throw std::invalid_argument("Unable to calculate inverse matrix for matrix with zero determinant.");
        }

        det = 1.0 / det;

        for (size_t i = 0; i < 16; i++) {
            inv[i] = inv[i] * det;
        }

        return Matrix(std::array<float, 16>({inv[0],inv[1],inv[2],inv[3],inv[4],inv[5],inv[6],inv[7],inv[8],inv[9],inv[10],inv[11],inv[12],inv[13],inv[14],inv[15]}));
    }

    Matrix Matrix::transpose() const
    {
        return Matrix({
            data[0], data[4], data[8], data[12],
            data[1], data[5], data[9], data[13],
            data[2], data[6], data[10], data[14],
            data[3], data[7], data[11], data[15],
        });
    }

    bool isEqual(const Matrix& m1, const Matrix& m2, const float precision)
    {
        for(size_t i = 0; i < 16; ++i)
        {
            float diff = std::abs(m2(i) - m1(i));
            if(diff > precision)
            {
                return false;
            }
        }
        return true;
    }

    Matrix inverse(const Matrix& m)
    {
        return m.inverse();
    }

    Matrix transpose(const Matrix& m)
    {
        return m.transpose();
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

        // TODO: w is only needed for perspective projection, not needed for rigid body & affine transformations
        float w = p[Axis::X]*m(Matrix::WX) + p[Axis::Y]*m(Matrix::WY) + p[Axis::Z]*m(Matrix::WZ) + m(Matrix::WW);
        auto result = Point({
            p[Axis::X]*m(Matrix::XX) + p[Axis::Y]*m(Matrix::XY) + p[Axis::Z]*m(Matrix::XZ) + m(Matrix::XW),
            p[Axis::X]*m(Matrix::YX) + p[Axis::Y]*m(Matrix::YY) + p[Axis::Z]*m(Matrix::YZ) + m(Matrix::YW),
            p[Axis::X]*m(Matrix::ZX) + p[Axis::Y]*m(Matrix::ZY) + p[Axis::Z]*m(Matrix::ZZ) + m(Matrix::ZW)
        });

        if(std::abs(w) > 1E-06)
        {
            result /= w;
        }

        return result;
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

    Matrix orthographicProjection(float left, float right, float top, float bottom, float N, float F)
    {
        return geometry::Matrix({
            2 / (right - left), 0, 0, -(right + left) / (right - left),
            0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
            0, 0, -2 / (F - N), (F + N) / (F - N),
            0, 0, 0, 1
        });
    }

    Matrix perspectiveTransformation(float N, float F)
    {
        float a = -(F+N) / (F-N);
        float b = -(2*F*N)/(F-N);
        return geometry::Matrix({
            N, 0, 0, 1,
            0, N, 0, 1,
            0, 0, a, b,
            0, 0, -1, 0
        });
    }

} // namespace geometry