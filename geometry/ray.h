#pragma once

#include "point.h"
#include "vector.h"

namespace geometry
{
    class Ray
    {
    public:
        Ray(const geometry::Point& origin, const geometry::Vector& direction);
        Ray(const geometry::Point& origin, const geometry::Point& anotherPoint);

        const geometry::Point& getOrigin() const;
        const geometry::Vector& getDirection() const;
    private:
        geometry::Point origin;
        geometry::Vector direction;
    };
}//namespace geometry

