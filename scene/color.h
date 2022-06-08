#pragma once

#include <array>
#include <cstddef>

/// RGB color
class Color
{
public:
    static const size_t R = 0;
    static const size_t G = 1;
    static const size_t B = 2;
    static const size_t A = 3;

    Color(float r, float g, float b, float a = 1.0);

    float& operator[](size_t index);
    const float& operator[](size_t index) const;
private:
    std::array<float, 4>    data;
};

Color operator*(const Color& c, float k);
Color operator*(float k, const Color& c);
Color operator+(const Color& c1, const Color& c2);

namespace Colors
{
    const Color White(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Red(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Green(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Blue(0.0f, 0.0f, 1.0f, 1.0f);

    const Color Yellow(1.0f, 1.0f, 0.0f, 1.0f);
    const Color Purple(1.0f, 0.0f, 1.0f, 1.0f);
    const Color Orange(1.0f, 0.3137f, 0.0f, 1.0f);


    const Color GrassGreen(0.0f, 0.603f, 0.0901f, 1.0f);
    const Color SkyBlue(0.529f, 0.808f, 0.922f, 1.0f);
}