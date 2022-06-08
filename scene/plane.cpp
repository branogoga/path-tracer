#include <iostream>
#include "plane.h"

Plane::Plane(const geometry::Vector& n, float d) : n(n), d(d)
{
}

const geometry::Vector& Plane::getNormal() const
{
    return n;
}

float Plane::getOffset() const
{
    return d;
}

bool intersect(const geometry::Ray& ray, const Plane& plane)
{
    float precision = 1E-06;
    float denominator = dot(plane.getNormal(), ray.getDirection());
    if(std::abs(denominator) < precision)
    {
        return false;
    }
    float t = (plane.getOffset() - dot(plane.getNormal(), ray.getOrigin() - geometry::Point({0.0, 0.0, 0.0}))) / denominator;

//    std::cout << "Intersect ray(origin="<<ray.getOrigin()<<", direction="<<ray.getDirection()<<") "
//                 "and plane(n="<<plane.getNormal()<<", d=" << plane.getOffset() << ") is t=" << t
//                 << std::endl;

    return t > 0;
}
