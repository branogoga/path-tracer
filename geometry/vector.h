#pragma once

#include <array>

namespace geometry {
    class Vector {
    public:
        Vector();

        float& operator[](const int index);
        const float& operator[](const int index) const;
    private:
        std::array<float, 2> data;
    };
}