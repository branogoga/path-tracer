#include "axis.h"
#include "point.h"
#include "vector.h"

namespace geometry {
    Point::Point() {
    }

    Point::Point(const std::array<float, 3> &data) : data(data) {
    }

    size_t Point::dimension() const {
        return data.size();
    }

    float& Point::operator[](const int index) {
        return data[index];
    }

    const float& Point::operator[](const int index) const {
        return data[index];
    }

    bool Point::operator==(const Point& v) const {
        return data == v.data;
    }

    bool Point::operator!=(const Point& v) const {
        return data != v.data;
    }

    bool isEqual(const Point& p1, const Point& p2, const float precision) {
        bool result = true;
        for(size_t i =  0; i <  p1.dimension() && result; ++i) {
            result &= std::abs(p2[i] - p1[i]) < precision;
        }
        return result;
    }

    Point& Point::operator+=(const Vector& v) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] += v[i];
        }
        return *this;
    }

    Point& Point::operator-=(const Vector& v) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] -= v[i];
        }
        return *this;
    }

    Point& Point::operator*=(float scale) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] *= scale;
        }
        return *this;
    }

    Point& Point::operator/=(float scale) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] /= scale;
        }
        return *this;
    }

    Point operator+(Point p, const Vector& v)
    {
        p += v;
        return p;

    }

    Vector operator-(const Point& p1, const Point& p2)
    {
        return Vector({p1[Axis::X]-p2[Axis::X], p1[Axis::Y]-p2[Axis::Y], p1[Axis::Z]-p2[Axis::Z]});
    }

    Point operator*(float scale, Point p)
    {
        p *= scale;
        return p;
    }

    Point operator*(Point p, float scale)
    {
        p *= scale;
        return p;
    }

}//namespace geometry

std::ostream& operator<<(std::ostream& out, const geometry::Point& p)
{
    out << "[" << p[geometry::Axis::X] << ", " <<  p[geometry::Axis::Y] << ", " << p[geometry::Axis::Z] <<"]";
    return out;
}
