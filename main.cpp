#include <complex>
#include "image/image.h"
#include "image/io/png.h"
#include "geometry/point.h"
#include "scene/sphere.h"
#include "scene/color.h"
#include "geometry/ray.h"
#include "scene/plane.h"
#include "utils/timer.h"

Color shading(
        const geometry::Point& intersectionPoint,
        const geometry::Vector& surfaceNormal,
        const geometry::Point& /*cameraOrigin*/,
        const geometry::Point& lightOrigin,// TODO: Infinite light sources like "sky"
        const Color& lightColor,// TODO: Multiple light sources
        const Color& materialColor,
        const Color& materialDiffusivity,
        const Color& materialReflectivity,
        const float materialReflectiveExponent,
        const Color& ambientLightCoeficient
        )
{
    auto s = normalize(intersectionPoint - lightOrigin);
    auto n = normalize(surfaceNormal);// TODO: require normalized, reduce duplication
    auto r = 2 * dot(s, n) / dot(n, n) * n - s;// Reflected-direction
    const float lambert = std::max(dot(s, n), 0.0f);
    const float phong = std::pow(std::max(dot(r, n), 0.0f), materialReflectiveExponent);
    auto lightingCoefficient = ambientLightCoeficient + materialDiffusivity * lambert + materialReflectivity * phong;
    lightingCoefficient[Color::R]=std::min(lightingCoefficient[Color::R], 1.0f);
    lightingCoefficient[Color::G]=std::min(lightingCoefficient[Color::G], 1.0f);
    lightingCoefficient[Color::B]=std::min(lightingCoefficient[Color::B], 1.0f);
    return materialColor * lightColor * lightingCoefficient;
}

int main(int /*argc*/, char **/*argv[]*/)
{
    Timer timer("Calculation of ray-traced scene took ");

    const auto colorBackground = Colors::SkyBlue;
    const auto colorObject = Colors::Red;
    const auto colorGround = Colors::GrassGreen;

    const auto ground = Plane(geometry::Vector({0.0f, 1.0f, 0.0f}), +1.0);

    const std::vector<Sphere> objects = {
            Sphere(geometry::Point({0.0f, 0.0f, -10.0f}), 5.0f),
    };

    const geometry::Point lightOrigin({0.0, 15.0, -20.0});
    const auto lightColor = Colors::White;

    auto image = Image(512, 512);
    for(size_t row = 0; row < image.getHeight(); ++row) {
        for(size_t column = 0; column < image.getWidth(); ++column) {

            // Cast ray from Camera origin [0, 0, 0] through the viewport [-1, -1] - [+1, +1] in plane z=-1
            geometry::Point cameraOrigin({0.0, 0.0, 0.0});
            // TODO: Center of pixel?
            geometry::Point pixel({2*((float)column/image.getWidth())-1.0f, 2*((float)row/image.getHeight())-1.0f, -1.0f});
            geometry::Ray ray = geometry::Ray(cameraOrigin, pixel);

            auto color = colorBackground;
            if(hasIntersection(ray, ground))
            {
                color = colorGround;
            }
            for(auto object : objects)
            {
                if(hasIntersection(ray, object))
                {
                    auto intersections = getAllIntersections(ray, object);

                    float closestIntersection = intersections[0];
                    for(auto intersection : intersections)
                    {
                        closestIntersection = std::min(intersection, closestIntersection);
                    }

                    auto intersectionPoint = ray(closestIntersection);
                    auto surfaceNormal = getNormal(intersectionPoint, object);

                    const Color ambientLightCoefficient(0.00f, 0.0f, 0.0f);
                    const Color diffusivity(0.75, 0.75, 0.75);
                    const Color materialReflectivity(0.75, 0.75, 0.75);
                    const float materialReflectiveExponent = 25.0;
                    // TODO: Overwrite shading only for closes intersection amongst all the objects !!!
                    color = shading(
                        intersectionPoint, surfaceNormal, cameraOrigin,
                        lightOrigin, lightColor, colorObject,
                        diffusivity, materialReflectivity, materialReflectiveExponent, ambientLightCoefficient
                    );
                }
            }
            image.setPixel(
                row, column,
                {
                    static_cast<unsigned char>(color[Color::R]*255),
                    static_cast<unsigned char>(color[Color::G]*255),
                    static_cast<unsigned char>(color[Color::B]*255),
                    static_cast<unsigned char>(color[Color::A]*255)
                }
            );
        }
    }

    savePng("main.png", image);

    return EXIT_SUCCESS;
}