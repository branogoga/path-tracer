#pragma once

#include "../geometry/point.h"
#include "../geometry/ray.h"

class Sphere
{
public:
    Sphere(const geometry::Point& origin, const float radius);

    float   getRadius() const;
    const geometry::Point& getOrigin() const;
private:
    geometry::Point   origin;
    float radius;
};

bool intersect(const geometry::Ray& ray, const Sphere& sphere);
