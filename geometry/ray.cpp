#include "ray.h"

namespace geometry
{

    Ray::Ray(const geometry::Point& origin, const geometry::Vector& direction) : origin(origin), direction(direction)
    {

    }

    Ray::Ray(const geometry::Point& origin, const geometry::Point& anotherPoint) : Ray(origin, anotherPoint - origin)
    {

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
