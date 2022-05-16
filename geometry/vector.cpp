#include "vector.h"

#include <cmath>

namespace geometry {
    Vector::Vector() {
    }

    Vector::Vector(const std::array<float, 3>& data): data(data) {
    }

    size_t Vector::dimension() const {
        return data.size();
    }

    float& Vector::operator[](const int index) {
        return data[index];
    }

    const float& Vector::operator[](const int index) const {
        return data[index];
    }

    Vector& Vector::operator+=(const Vector& v) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] += v[i];
        }
        return *this;
    }

    Vector& Vector::operator-=(const Vector& v) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] -= v[i];
        }
        return *this;
    }

    float Vector::length2() const {
        return dot(*this);
    }

    float Vector::length() const {
        return sqrt(length2());
    }

    float Vector::dot(const Vector& v) const {
        float sum = 0.0f;
        for(size_t i = 0; i <  data.size(); ++i) {
            sum += data[i]*v[i];
        }
        return sum;
    }

    Vector Vector::cross(const Vector& v) const {
        return Vector({
            (data[1] * v[2]) - (data[2] * v[1]),
            (data[2] * v[0]) - (data[0] * v[2]),
            (data[0] * v[1]) - (data[1] * v[0])
        });
    }

    void Vector::normalize() {
        *this /= length();
    }

    Vector& Vector::operator*=(float scale) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] *= scale;
        }
        return *this;
    }

    Vector& Vector::operator/=(float scale) {
        for(size_t i = 0; i <  data.size(); ++i) {
            data[i] /= scale;
        }
        return *this;
    }

    bool Vector::operator==(const Vector& v) const {
        return data == v.data;
    }

    bool Vector::operator!=(const Vector& v) const {
        return data != v.data;
    }

    Vector operator+(Vector lhs, const Vector& rhs) {
        lhs += rhs;
        return lhs;
    }

    Vector operator*(float scale, Vector vector) {
        vector *= scale;
        return vector;
    }

    Vector operator*(Vector vector, float scale) {
        vector *= scale;
        return vector;
    }

    Vector normalize(Vector v) {
        v.normalize();
        return v;
    }

    float length(const Vector& v) {
        return v.length();
    }

    float length2(const Vector& v) {
        return v.length2();
    }

    float dot(const Vector& v1, const Vector& v2) {
        return v1.dot(v2);
    }

    Vector cross(const Vector& v1, const Vector& v2) {
        return v1.cross(v2);
    }

    bool isEqual(const Vector& v1, const Vector& v2, const float precision) {
        bool result = true;
        for(size_t i =  0; i <  v1.dimension() && result; ++i) {
            result &= std::abs(v2[i] - v1[i]) < precision;
        }
        return result;
    }

    float angle(const Vector& v1, const Vector& v2) {
        return acos(dot(v1,v2) / sqrt(v1.length2() * v2.length2()));
    }

} //namespace geometry