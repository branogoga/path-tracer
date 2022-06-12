#include "sphere.h"

#include "../geometry/axis.h"
#include "../math/quadratic_solver.h"

#include <algorithm>
#include <complex>

using namespace geometry;

Sphere::Sphere(const geometry::Point& origin, const float radius) : origin(origin), radius(radius)
{
}

float   Sphere::getRadius() const
{
    return radius;
}

const geometry::Point& Sphere::getOrigin() const
{
    return origin;
}

bool Sphere::hasIntersection(const geometry::Ray& ray)
{
    return ::hasIntersection(ray, *this);
}

std::vector<float> Sphere::getAllIntersections(const geometry::Ray& ray)
{
    return ::getAllIntersections(ray, *this);
}

geometry::Vector Sphere::getNormal(const geometry::Point& intersectionPoint)
{
    return ::getNormal(intersectionPoint, *this);
}

TextureCoordinates Sphere::getTextureCoordinates(const geometry::Point& intersectionPoint)
{
    return ::getTextureCoordinates(intersectionPoint, *this);
}

bool hasIntersection(const geometry::Ray& ray, const Sphere& sphere)
{
    geometry::Vector L = ray.getOrigin() - sphere.getOrigin();
    geometry::Vector d = ray.getDirection();
    float r = sphere.getRadius();
    float a = dot(d,d);
    float b = 2*dot(d,L);
    float c = dot(L,L) - r*r;

    return QuadraticEquation(a, b, c).hasRoot();
}

std::vector<float> getAllIntersections(const geometry::Ray& ray, const Sphere& sphere)
{
    geometry::Vector L = ray.getOrigin() - sphere.getOrigin();
    geometry::Vector d = ray.getDirection();
    float r = sphere.getRadius();
    float a = dot(d,d);
    float b = 2*dot(d,L);
    float c = dot(L,L) - r*r;

    auto roots = QuadraticEquation(a, b, c).getRoots();
    roots.erase(
        std::remove_if(
            roots.begin(),
            roots.end(),
            [](float x){return x < 0;}
        ),
        roots.end()
    );
    return roots;
}

geometry::Vector getNormal(const geometry::Point& point, const Sphere& sphere)
{
    return normalize(point - sphere.getOrigin());
}

TextureCoordinates toSphericalCoordinates(const Vector& v)
{
    float radius = length(v);
    float phi = std::acos(v[Axis::Z]/radius);
    float theta = std::atan2(v[Axis::Y],v[Axis::X]);
    return TextureCoordinates(phi, theta);
}

Vector toCartesianCoordinates(float phi, float theta, float radius)
{
    return Vector({
        std::cos(theta) * std::cos(phi) * radius,
        std::sin(theta) * std::cos(phi) * radius,
        std::sin(phi) * radius
    });
}

TextureCoordinates getTextureCoordinates(const geometry::Point& point, const Sphere& sphere)
{
    auto v = point - sphere.getOrigin();
    return toSphericalCoordinates(v);
}
