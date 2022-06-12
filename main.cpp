#include <complex>
#include <memory>
#include <algorithm>
#include "image/image.h"
#include "image/io/png.h"
#include "geometry/point.h"
#include "scene/sphere.h"
#include "scene/color.h"
#include "geometry/ray.h"
#include "scene/plane.h"
#include "utils/timer.h"
#include "scene/material.h"
#include "scene/object.h"

int main(int /*argc*/, char **/*argv[]*/)
{
    Timer timer("Calculation of ray-traced scene took ");

    const auto colorBackground = Colors::SkyBlue;

    const Material materialGrass(
            Colors::White,
            Color(0.0, 0.0, 0.0),
            Color(0.0, 0.0, 0.0),
            1.0,
            Colors::GrassGreen
            );

    auto groundPlane = std::make_shared<Plane>(geometry::Vector({0.0f, +1.0f, 0.0f}), +2.5);
    auto bigSphere = std::make_shared<Sphere>(geometry::Point({0.0f, 0.0f, -15.0f}), 5.0f);
    auto smallSphere = std::make_shared<Sphere>(geometry::Point({1.5f, 2.0f, -10.0f}), 1.0f);
    std::vector<std::shared_ptr<Object>> objects = {
        std::make_shared<Object>(groundPlane, materialGrass),
        std::make_shared<Object>(bigSphere, Materials::Bronze),
        std::make_shared<Object>(smallSphere, Materials::BlackPlastic)
    };

    const geometry::Point lightOrigin({0.0, -2.5, 0.0});
    const auto lightColor = Colors::White;

    auto image = Image(512, 512);
    for(size_t row = 0; row < image.getHeight(); ++row) {
        for(size_t column = 0; column < image.getWidth(); ++column) {

            // Cast ray from Camera origin [0, 0, 0] through the viewport [-1, -1] - [+1, +1] in plane z=-1
            geometry::Point cameraOrigin({0.0, 0.01, 0.0});
            // TODO: Center of pixel?
            geometry::Point pixel({2*((float)column/image.getWidth())-1.0f, 2*((float)row/image.getHeight())-1.0f, -1.0f});
            geometry::Ray ray = geometry::Ray(cameraOrigin, pixel);

            auto color = colorBackground;
            struct Intersection
            {
                Intersection(float t, std::shared_ptr<Object> object) : t(t), object(object) {};

                float t;
                std::shared_ptr<Object> object;
            };
            std::vector<Intersection> intersections = {};

            for(auto object : objects) {
                if (object->getShape()->hasIntersection(ray)) {
                    const auto objectIntersections = object->getShape()->getAllIntersections(ray);
                    for (auto intersection: objectIntersections) {
                        intersections.emplace_back(Intersection(intersection, object));
                    }
                }
            }

            if(!intersections.empty()) {
                std::sort(intersections.begin(), intersections.end(),
                          [](const Intersection &a, const Intersection &b) { return a.t < b.t; });

                Intersection closestIntersection = *intersections.begin();
                const auto intersectionPoint = ray(closestIntersection.t);
                const auto surfaceNormal = closestIntersection.object->getShape()->getNormal(intersectionPoint);

                // TODO: Overwrite shading only for closes intersection amongst all the objects !!!
                // TODO: Cast shadow-ray to find out if the light is visible from the hit-point (or which portion of the light)
                // TODO: Add emitted light of the object
                color = closestIntersection.object->getMaterial().calculateLighting(
                    intersectionPoint, surfaceNormal, cameraOrigin,
                    lightOrigin, lightColor
                );
                // TODO: Add reflected and refracted color
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