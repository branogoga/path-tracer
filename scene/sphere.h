#pragma once

#include <vector>
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

bool hasIntersection(const geometry::Ray& ray, const Sphere& sphere);
std::vector<float> getAllIntersections(const geometry::Ray& ray, const Sphere& sphere);
geometry::Vector getNormal(const geometry::Point& point, const Sphere& sphere);
