#include "object.h"

TextureCoordinates::TextureCoordinates(float u, float v) : u(u), v(v) {}

Object::Object(std::shared_ptr<Shape> shape, const Material& material) : material(material), shape(shape) {}

const Material& Object::getMaterial() const
{
    return material;
}

std::shared_ptr<Shape> Object::getShape() const
{
    return shape;
}
