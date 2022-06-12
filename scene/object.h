#pragma once

class Object
{
public:
    Object() {};
    virtual ~Object() = default;

    virtual bool hasIntersection(const geometry::Ray& ray) = 0;
    virtual std::vector<float> getAllIntersections(const geometry::Ray& ray) = 0;
    virtual geometry::Vector getNormal(const geometry::Point&) = 0;
};