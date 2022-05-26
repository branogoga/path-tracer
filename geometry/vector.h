#pragma once

#include <array>

namespace geometry {

    enum Axis {
        X = 0,
        Y = 1,
        Z = 2,
        W = 3
    };

    class Vector {
    public:
        Vector();
        Vector(const std::array<float, 3>& data);

        size_t dimension() const;

        float& operator[](const int index);
        const float& operator[](const int index) const;

        Vector& operator+=(const Vector& v);
        Vector& operator-=(const Vector& v);
        Vector& operator*=(float scale);
        Vector& operator/=(float scale);

        float length() const;
        float length2() const;
        float dot(const Vector& v) const;
        Vector cross(const Vector& v) const;
        void normalize();

        bool operator==(const Vector& v) const;
        bool operator!=(const Vector& v) const;

    private:
        std::array<float, 3> data;
    };

    Vector operator+(Vector rhs, const Vector& lhs);
    Vector operator*(float scale, Vector vector);
    Vector operator*(Vector vector, float scale);
    bool isEqual(const Vector& v1, const Vector& v2, const float precision = 1E-06);

    float length(const Vector& v);
    float length2(const Vector& v);
    float dot(const Vector& v1, const Vector& v2);
    Vector normalize(Vector v);
    Vector cross(const Vector& v1, const Vector& v2);
    float angle(const Vector& v1, const Vector& v2);

} //namespace geometry