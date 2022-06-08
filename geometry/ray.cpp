#include "ray.h"

namespace geometry
{

    Ray::Ray(const geometry::Point& origin, const geometry::Vector& direction) : origin(origin), direction(direction)
    {
    }

    Ray::Ray(const geometry::Point& origin, const geometry::Point& anotherPoint) : Ray(origin, anotherPoint - origin)
    {
    }

    geometry::Point Ray::operator()(float t) const
    {
        return origin + t*direction;
    }

    const geometry::Point& Ray::getOrigin() const
    {
        return origin;
    }

    const geometry::Vector& Ray::getDirection() const
    {
        return direction;
    }

}//namespace geometry
