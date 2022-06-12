#pragma once

#include "color.h"
#include "../geometry/point.h"
#include "../geometry/vector.h"

class Material
{
public:
    Material(Color color, Color diffusivity, Color reflectivity, float reflectionExponent, const Color& ambientLightCoeficient
    );

    Color   calculateLighting(
            const geometry::Point& intersectionPoint,
            const geometry::Vector& surfaceNormal,
            const geometry::Point& /*cameraOrigin*/,
            const geometry::Point& lightOrigin,// TODO: Infinite light sources like "sky"
            const Color& lightColor // TODO: Multiple light sources
            ) const;

private:
    Color color;
    bool  isDiffusive;
    Color diffusivity;
    bool  isReflective;
    Color reflectivity;
    float reflectionExponent;
    Color ambientLightCoeficient;
};

namespace Materials
{
    const Material BlackPlastic(
            Colors::White,
            Color(0.01, 0.01, 0.01),
            Color(0.5, 0.5, 0.5),
            32,
            Color(0.0, 0.0, 0.0)
            );

    const Material Brass(
            Colors::White,
            Color(0.780392, 0.568627, 0.113725),
            Color(0.992157, 0.941176, 0.807843),
            27.8974,
            Color(0.329412, 0.223529, 0.027451)
    );

    const Material Bronze(
            Colors::White,
            Color(0.714, 0.4284, 0.18144),
            Color(0.393548, 0.271906, 0.166721),
            25.6,
            Color(0.2125, 0.1275, 0.054)
    );

    const Material Chrome(
            Colors::White,
            Color(0.4, 0.4, 0.4),
            Color(0.774597, 0.774597, 0.774597),
            76.8,
            Color(0.25, 0.25, 0.25)
    );

    const Material Copper(
            Colors::White,
            Color(0.7038, 0.27048, 0.0828),
            Color(0.256777, 0.137622, 0.086014),
            12.8,
            Color(0.19125, 0.0735, 0.0225)
    );

    const Material Gold(
            Colors::White,
            Color(0.75164, 0.60648, 0.22648),
            Color(0.628281, 0.555802, 0.366065),
            51.2,
            Color(0.24725, 0.1995, 0.0745)
    );

    const Material Pewter(
            Colors::White,
            Color(0.427451, 0.470588, 0.541176),
            Color(0.3333, 0.3333, 0.521569),
            9.84615,
            Color(0.10588, 0.058824, 0.113725)
    );

    const Material Silver(
            Colors::White,
            Color(0.50754, 0.50754, 0.50754),
            Color(0.508273, 0.508273, 0.508273),
            51.2,
            Color(0.19225, 0.19225, 0.19225)
    );

    const Material PolishedSilver(
            Colors::White,
            Color(0.2775, 0.2775, 0.2775),
            Color(0.773911, 0.773911, 0.773911),
            89.6,
            Color(0.23125, 0.23125, 0.23125)
    );
}//namespace Materials