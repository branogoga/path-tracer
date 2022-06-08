#pragma once

#include <cstddef>
#include <vector>

/// Quadratic equation a*x^2 + b*x + c = 0
class QuadraticEquation
{
public:
    QuadraticEquation(float a, float b, float c);

    bool hasRoot() const;
    size_t getNumberOfRoots() const;
    std::vector<float> getRoots() const;

    float discriminant() const;

private:
    float a;
    float b;
    float c;
};