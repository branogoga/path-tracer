#include "vector.h"

namespace geometry {
    Vector::Vector() {
    }

    float& Vector::operator[](const int index) {
        return data[index];
    }

    const float& Vector::operator[](const int index) const {
        return data[index];
    }

}