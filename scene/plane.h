# pragma once

#include "../geometry/vector.h"
#include "../geometry/ray.h"

class Plane
{
public:
    Plane(const geometry::Vector& n, float d);


    const geometry::Vector& getNormal() const;
    float getOffset() const;

private:
    geometry::Vector n;
    float   d;
};

bool intersect(const geometry::Ray& ray, const Plane& plane);
