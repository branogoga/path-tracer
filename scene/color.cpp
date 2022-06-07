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

