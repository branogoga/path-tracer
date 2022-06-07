#include "camera.h"

#include <stdexcept>

const float Precision = 1E-06;

Camera::Camera(float left, float right, float top, float bottom, float N, float F)
{
    if(std::abs(right - left) < Precision)
    {
        throw std::invalid_argument("Unable to create Camera: Left and right must differ.");
    }

    if(std::abs(top - bottom) < Precision)
    {
        throw std::invalid_argument("Unable to create Camera: Top and bottom must differ.");
    }

    if(std::abs(F - N) < Precision)
    {
        throw std::invalid_argument("Unable to create Camera: Far and N must differ.");
    }

    worldToNormalizedScreenTransformation = geometry::orthographicProjection(left, right, top, bottom, N, F);
    normalizedScreenToWorldTransformation = worldToNormalizedScreenTransformation.inverse();
}

geometry::Matrix    Camera::getWorldToNormalizedScreenTransformation() const
{
    return worldToNormalizedScreenTransformation;
}

geometry::Matrix    Camera::getNormalizedScreenToWorldTransformation() const
{
    return normalizedScreenToWorldTransformation;
}
