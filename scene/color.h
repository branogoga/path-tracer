#pragma once

#include <array>
#include <cstddef>

class Color
{
public:
    static const size_t R = 0;
    static const size_t G = 1;
    static const size_t B = 2;
    static const size_t A = 3;

    static const Color White();

    Color(float r, float g, float b, float a = 1.0);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;
private:
    std::array<float, 4>    data;
};