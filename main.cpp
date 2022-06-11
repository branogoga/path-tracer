#include <complex>
#include "image/image.h"
#include "image/io/png.h"
#include "geometry/point.h"
#include "scene/sphere.h"
#include "scene/color.h"
#include "geometry/ray.h"
#include "scene/plane.h"
#include "utils/timer.h"
#include "scene/material.h"

int main(int /*argc*/, char **/*argv[]*/)
{
    Timer timer("Calculation of ray-traced scene took ");

    const auto colorBackground = Colors::SkyBlue;
    const auto colorGround = Colors::GrassGreen;

    const auto ground = Plane(geometry::Vector({0.0f, 1.0f, 0.0f}), +1.0);

    const std::vector<Sphere> objects = {
            Sphere(geometry::Point({0.0f, 0.0f, -10.0f}), 5.0f),
    };

    Material sphereMaterial = Materials::Bronze;

    const geometry::Point lightOrigin({0.0, -2.5, 0.0});
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

                    // TODO: Overwrite shading only for closes intersection amongst all the objects !!!
                    color = sphereMaterial.calculateLighting(
                        intersectionPoint, surfaceNormal, cameraOrigin,
                        lightOrigin, lightColor
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