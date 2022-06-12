#include <complex>
#include "material.h"

Material::Material(Color color, Color diffusivity, Color reflectivity, float reflectionExponent, const Color& ambientLightCoeficient)
    : color(color)
    , diffusivity(diffusivity)
    , reflectivity(reflectivity)
    , reflectionExponent(reflectionExponent)
    , ambientLightCoeficient(ambientLightCoeficient)
{
    isDiffusive = diffusivity[Color::R] > 0.0 && diffusivity[Color::G] > 0.0 && diffusivity[Color::B] > 0.0;
    isReflective = reflectivity[Color::R] > 0.0 && reflectivity[Color::G] > 0.0 && reflectivity[Color::B] > 0.0;
}

Color   Material::calculateLighting(
        const geometry::Point& intersectionPoint,
        const geometry::Vector& surfaceNormal,
        const geometry::Point& /*cameraOrigin*/,
        const geometry::Point& lightOrigin,// TODO: Infinite light sources like "sky"
        const Color& lightColor // TODO: Multiple light sources
) const
{
    auto lightingCoefficient = ambientLightCoeficient;
    if(isDiffusive || isReflective) {
        auto n = normalize(surfaceNormal);// TODO: require normalized, reduce duplication
        auto s = normalize(lightOrigin - intersectionPoint);
        if (isDiffusive) {
            const float lambert = std::max(dot(s, n), 0.0f);
            lightingCoefficient += diffusivity * lambert;
        }
        if (isReflective) {
            auto r = reflect(s, n);
            const float phong = std::pow(std::max(dot(r, n), 0.0f), reflectionExponent);
            lightingCoefficient += reflectivity * phong;
        }
        lightingCoefficient[Color::R]=std::min(lightingCoefficient[Color::R], 1.0f);
        lightingCoefficient[Color::G]=std::min(lightingCoefficient[Color::G], 1.0f);
        lightingCoefficient[Color::B]=std::min(lightingCoefficient[Color::B], 1.0f);
    }
    return color * lightColor * lightingCoefficient;
}
