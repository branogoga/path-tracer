#include "color.h"

Color::Color(float r, float g, float b, float a): data({r,g,b,a})
{
}

float& Color::operator[](size_t index)
{
    return data[index];
}

const float& Color::operator[](size_t index) const
{
    return data[index];
}

Color operator*(const Color& c, float k)
{
    // TODO: How to work with alpha channel?
    return Color({
     k * c[Color::R],
     k * c[Color::G],
     k * c[Color::B],
     });
}

Color operator*(float k, const Color& c)
{
    return c*k;
}

Color operator*(const Color& c1, const Color& c2)
{
    // TODO: How to work with alpha channel?
    return Color({
     c1[Color::R] * c2[Color::R],
     c1[Color::G] * c2[Color::G],
     c1[Color::B] * c2[Color::B],
    });
}

Color operator+(const Color& c1, const Color& c2)
{
    // TODO: How to work with alpha channel?
    return Color({
        c1[Color::R] + c2[Color::R],
        c1[Color::G] + c2[Color::G],
        c1[Color::B] + c2[Color::B],
    });
}


