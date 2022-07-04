#include "quadratic_solver.h"

#include <cmath>

constexpr float precision = 1E-06;

QuadraticEquation::QuadraticEquation(float a, float b, float c): a(a), b(b), c(c)
{
}

bool QuadraticEquation::isQuadratic() const
{
    return degree() == 2;
}

bool QuadraticEquation::isLinear() const
{
    return degree() == 1;
}

bool QuadraticEquation::isConstant() const
{
    return degree() == 0;
}

unsigned QuadraticEquation::degree() const
{
    if(std::abs(a) > precision)
    {
        return 2;
    }
    else if (std::abs(b) > precision)
    {
        return 1;
    }

    return 0;
}

float QuadraticEquation::discriminant() const
{
    return b*b - 4*a*c;
}

bool QuadraticEquation::hasRoot() const
{
    const auto polynomial_degree = degree();
    if(polynomial_degree == 2) {
        return discriminant() >= 0.0f;
    }
    else if (polynomial_degree == 1) {
        return true;
    }

    return std::abs(c) < precision;
}

size_t QuadraticEquation::getNumberOfRoots() const
{
    float D = discriminant();
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
    const auto polynomial_degree = degree();
    if(polynomial_degree == 2)
    {
        // Quadratic equation
        float D = discriminant();
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
    else if (polynomial_degree == 1)
    {
        // Linear equation
        return {-c/b};
    }

    // Constant equation
    if(std::abs(c) < precision)
    {
        return { 0.0f };
    }

    return {};
}
