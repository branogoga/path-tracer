#include <complex>
#include "material.h"

Material::Material(Color color, Color diffusivity, Color reflectivity, float reflectionExponent)
    : color(color), diffusivity(diffusivity), reflectivity(reflectivity), reflectionExponent(reflectionExponent)
{
}

Color   Material::calculateLighting(
        const geometry::Point& intersectionPoint,
        const geometry::Vector& surfaceNormal,
        const geometry::Point& /*cameraOrigin*/,
        const geometry::Point& lightOrigin,// TODO: Infinite light sources like "sky"
        const Color& lightColor,// TODO: Multiple light sources
        const Color& ambientLightCoeficient
) const
{
    auto s = normalize(lightOrigin - intersectionPoint);
    auto n = normalize(surfaceNormal);// TODO: require normalized, reduce duplication
    auto r = 2 * dot(s, n) / dot(n, n) * n - s;// Reflected-direction
    const float lambert = std::max(dot(s, n), 0.0f);
    const float phong = std::pow(std::max(dot(r, n), 0.0f), reflectionExponent);
    auto lightingCoefficient = ambientLightCoeficient + diffusivity * lambert + reflectivity * phong;
    lightingCoefficient[Color::R]=std::min(lightingCoefficient[Color::R], 1.0f);
    lightingCoefficient[Color::G]=std::min(lightingCoefficient[Color::G], 1.0f);
    lightingCoefficient[Color::B]=std::min(lightingCoefficient[Color::B], 1.0f);
    return color * lightColor * lightingCoefficient;
}
