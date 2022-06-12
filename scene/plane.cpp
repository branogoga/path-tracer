#include <iostream>
#include "plane.h"
#include "../geometry/axis.h"

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

bool Plane::hasIntersection(const geometry::Ray& ray)
{
    return ::hasIntersection(ray, *this);
}

std::vector<float> Plane::getAllIntersections(const geometry::Ray& ray)
{
    return ::getAllIntersections(ray, *this);
}

geometry::Vector Plane::getNormal(const geometry::Point& intersectionPoint)
{
    return ::getNormal(intersectionPoint, *this);
}

TextureCoordinates Plane::getTextureCoordinates(const geometry::Point& intersectionPoint)
{
    return ::getTextureCoordinates(intersectionPoint, *this);
}

bool hasIntersection(const geometry::Ray& ray, const Plane& plane)
{
    return !getAllIntersections(ray, plane).empty();
}

std::vector<float> getAllIntersections(const geometry::Ray& ray, const Plane& plane)
{
    float precision = 1E-06;
    float denominator = dot(plane.getNormal(), ray.getDirection());
    if(std::abs(denominator) < precision)
    {
        return {};
    }
    float t = (plane.getOffset() - dot(plane.getNormal(), ray.getOrigin() - geometry::Point({0.0, 0.0, 0.0}))) / denominator;

//    std::cout << "Intersect ray(origin="<<ray.getOrigin()<<", direction="<<ray.getDirection()<<") "
//                 "and plane(n="<<plane.getNormal()<<", d=" << plane.getOffset() << ") is t=" << t
//                 << std::endl;

    // Only positive intersections (= in-front of camera)?
    if(t > precision) {
        return {t};
    } else {
        return {};
    }
}

geometry::Vector getNormal(const geometry::Point&, const Plane& plane)
{
    return plane.getNormal();
}

geometry::Vector getPrimaryTextureDirection(const geometry::Vector& n)
{
    // return geometry::Vector({ n[geometry::Axis::X], -n[geometry::Axis::Y], 0.0 });

    auto a = cross(n, geometry::Vector({1.0, 0.0, 0.0}));
    auto b = cross(n, geometry::Vector({0.0, 1.0, 0.0}));

    auto max_ab = dot(a, a) < dot(b, b) ? b : a;

    auto c = cross(n, geometry::Vector({0.0, 0.0, 1.0}));

    return normalize(dot(max_ab, max_ab) < dot(c, c) ? c : max_ab);
}

TextureCoordinates getTextureCoordinates(const geometry::Point& point, const Plane& plane)
{
    geometry::Vector n = plane.getNormal();
    geometry::Vector u = getPrimaryTextureDirection(n);
    geometry::Vector v = normalize(cross(n,u));
    geometry::Vector o = point - geometry::Point({0.0, 0.0, 0.0});

    return TextureCoordinates(
            geometry::dot(u, o),
            geometry::dot(v, o)
            );
}



