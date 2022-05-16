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

        float& operator[](const int index);
        const float& operator[](const int index) const;
    private:
        std::array<float, 3> data;
    };
}