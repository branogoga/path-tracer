#include "quadratic_solver.h"

#include <cmath>

QuadraticEquation::QuadraticEquation(float a, float b, float c): a(a), b(b), c(c)
{
}

float QuadraticEquation::discriminant() const
{
    return b*b - 4*a*c;
}

bool QuadraticEquation::hasRoot() const
{
    return discriminant() >= 0.0f;
}

size_t QuadraticEquation::getNumberOfRoots() const
{
    float D = discriminant();
    float precision = 1E-06;
    if(D > precision)
    {
        return 2;
    }
    else if(D < -precision)
    {
        return 0;
    }

    return 1;
}

std::vector<float> QuadraticEquation::getRoots() const
{
    float D = discriminant();
    float precision = 1E-06;
    if(D > precision)
    {
        float q = (b > 0) ?
                  -0.5 * (b + sqrt(D)) :
                  -0.5 * (b - sqrt(D));
        float x0 = q / a;
        float x1 = c / q;
        return {x0, x1};
    }
    else if(D < -precision)
    {
        return {};
    }

    return { -0.5f * b / a };

}
