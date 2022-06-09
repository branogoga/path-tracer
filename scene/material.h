#pragma once

#include "color.h"
#include "../geometry/point.h"
#include "../geometry/vector.h"

class Material
{
public:
    Material(Color color, Color diffusivity, Color reflectivity, float reflectionExponent);

    Color   calculateLighting(
            const geometry::Point& intersectionPoint,
            const geometry::Vector& surfaceNormal,
            const geometry::Point& /*cameraOrigin*/,
            const geometry::Point& lightOrigin,// TODO: Infinite light sources like "sky"
            const Color& lightColor,// TODO: Multiple light sources
            const Color& ambientLightCoeficient
            ) const;

private:
    Color color;
    Color diffusivity;
    Color reflectivity;
    float reflectionExponent;
};