#pragma once

#include "../geometry/matrix.h"

/// Perspective camera looking in the negative-Z direction
class Camera
{
public:
    Camera(float left, float right, float top, float bottom, float N, float F);

    // TODO: Camera transformation - position + rotation

    geometry::Matrix    getWorldToNormalizedScreenTransformation() const;
    geometry::Matrix    getNormalizedScreenToWorldTransformation() const;
private:
    geometry::Matrix worldToNormalizedScreenTransformation;
    geometry::Matrix normalizedScreenToWorldTransformation;
};