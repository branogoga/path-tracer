#include "vector.h"

namespace geometry {
    Vector::Vector(): data({0.0f, 0.0f, 0.0f}) {
    }

    float& Vector::operator[](const int index) {
        return data[index];
    }

    const float& Vector::operator[](const int index) const {
        return data[index];
    }

}