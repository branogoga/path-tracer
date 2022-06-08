#include "sphere.h"

#include "../math/quadratic_solver.h"

Sphere::Sphere(const geometry::Point& origin, const float radius) : origin(origin), radius(radius)
{
}

float   Sphere::getRadius() const
{
    return radius;
}

const geometry::Point& Sphere::getOrigin() const
{
    return origin;
}

bool intersect(const geometry::Ray& ray, const Sphere& sphere)
{
    geometry::Vector L = ray.getOrigin() - sphere.getOrigin();
    geometry::Vector d = ray.getDirection();
    float r = sphere.getRadius();
    float a = dot(d,d);
    float b = 2*dot(d,L);
    float c = dot(L,L) - r*r;

    return QuadraticEquation(a, b, c).hasRoot();
}
