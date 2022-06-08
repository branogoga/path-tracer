#include "image/image.h"
#include "image/io/png.h"
#include "geometry/point.h"
#include "scene/sphere.h"
#include "scene/color.h"
#include "geometry/ray.h"
#include "scene/plane.h"

#include <iostream>

int main(int /*argc*/, char **/*argv[]*/)
{
    std::cout << "Hello World!" << std::endl;

    const auto colorBackground = Colors::SkyBlue;
    const auto colorObject = Colors::Red;
    const auto colorGround = Colors::GrassGreen;

    const auto ground = Plane(geometry::Vector({0.0f, 1.0f, 0.0f}), +1.0);

    const std::vector<Sphere> objects = {
            Sphere(geometry::Point({0.0f, 0.0f, -10.0f}), 5.0f),
    };

    auto image = Image(100, 100);
    for(size_t row = 0; row < image.getHeight(); ++row) {
        for(size_t column = 0; column < image.getWidth(); ++column) {

            // Cast ray from Camera origin [0, 0, 0] through the viewport [-1, -1] - [+1, +1] in plane z=-1
            geometry::Point cameraOrigin({0.0, 0.0, 0.0});
            // TODO: Center of pixel?
            geometry::Point pixel({2*((float)column/image.getWidth())-1.0f, 2*((float)row/image.getHeight())-1.0f, -1.0f});
            geometry::Ray ray = geometry::Ray(cameraOrigin, pixel);

            auto color = colorBackground;
            if(intersect(ray, ground))
            {
                color = colorGround;
            }
            for(auto object : objects)
            {
                if(intersect(ray, object))
                {
                    color = colorObject;
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