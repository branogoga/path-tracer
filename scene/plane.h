# pragma once

#include <vector>
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

bool hasIntersection(const geometry::Ray& ray, const Plane& plane);
std::vector<float> getAllIntersections(const geometry::Ray& ray, const Plane& plane);
geometry::Vector getNormal(const geometry::Point&, const Plane& plane);
