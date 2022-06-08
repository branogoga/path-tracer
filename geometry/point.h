#pragma once

#include <array>

namespace geometry {

    class Vector;

    class Point {
    public:
        Point();
        Point(const std::array<float, 3>& data);

        size_t dimension() const;

        float& operator[](const int index);
        const float& operator[](const int index) const;

        Point& operator+=(const Vector& v);
        Point& operator-=(const Vector& v);
        Point& operator*=(float scale);
        Point& operator/=(float scale);

        bool operator==(const Point& v) const;
        bool operator!=(const Point& v) const;

    private:
        std::array<float, 3> data;
    };

    Point operator+(Point rhs, const Vector& lhs);
    Vector operator-(const Point& p1, const Point& p2);
    Point operator*(float scale, Point p);
    Point operator*(Point p, float scale);
    bool isEqual(const Point& v1, const Point& v2, const float precision = 1E-06);

} //namespace geometry

std::ostream& operator<<(std::ostream& out, const geometry::Point& p);
