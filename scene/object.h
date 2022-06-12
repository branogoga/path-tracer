#pragma once

#include "material.h"
#include "../geometry/ray.h"

#include <vector>
#include <memory>

struct TextureCoordinates
{
public:
    TextureCoordinates(float u, float v);

    float u;
    float v;
};

class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual bool hasIntersection(const geometry::Ray& ray) = 0;
    virtual std::vector<float> getAllIntersections(const geometry::Ray& ray) = 0;
    virtual geometry::Vector getNormal(const geometry::Point&) = 0;
    virtual TextureCoordinates getTextureCoordinates(const geometry::Point& point) = 0;
};

class Object
{
public:
    Object(std::shared_ptr<Shape> shape, const Material& material);
    virtual ~Object() = default;

    const Material& getMaterial() const;
    std::shared_ptr<Shape> getShape() const;
private:
    Material material;
    std::shared_ptr<Shape> shape;
};