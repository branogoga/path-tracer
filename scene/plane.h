# pragma once

#include <vector>
#include "../geometry/vector.h"
#include "../geometry/ray.h"
#include "object.h"

class Plane : public Shape
{
public:
    Plane(const geometry::Vector& n, float d);


    const geometry::Vector& getNormal() const;
    float getOffset() const;

    bool hasIntersection(const geometry::Ray& ray) override;
    std::vector<float> getAllIntersections(const geometry::Ray& ray) override;
    geometry::Vector getNormal(const geometry::Point& intersectionPoint) override;
    TextureCoordinates getTextureCoordinates(const geometry::Point& point) override;

private:
    geometry::Vector n;
    float   d;
};

bool hasIntersection(const geometry::Ray& ray, const Plane& plane);
std::vector<float> getAllIntersections(const geometry::Ray& ray, const Plane& plane);
geometry::Vector getNormal(const geometry::Point&, const Plane& plane);
TextureCoordinates getTextureCoordinates(const geometry::Point& point, const Plane& plane);

