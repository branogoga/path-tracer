#include "image/image.h"
#include "image/io/png.h"

#include <array>
#include <iostream>

int main(int /*argc*/, char **/*argv[]*/)
{
    std::cout << "Hello World!";

    const auto colorBackground = std::array<unsigned char, 4>({25, 25, 25, 255});
    const auto colorObject = std::array<unsigned char, 4>({255, 128, 128, 255});

    auto image = Image(100, 100);
    const auto halfWidth = image.getWidth()/ 2;
    const auto halfHeight = image.getHeight()/ 2;
    const auto radius = std::min(halfWidth, halfHeight);
    const auto radiusSqr = radius*radius;
    for(size_t row = 0; row < image.getHeight(); ++row) {
        for(size_t column = 0; column < image.getWidth(); ++column) {
            const auto xDiff = column - halfWidth;
            const auto yDiff = row - halfHeight;
            const auto distanceSqr = xDiff*xDiff + yDiff*yDiff;
            if(distanceSqr < radiusSqr) {
                image.setPixel(row, column, colorObject);
            } else {
                image.setPixel(row, column, colorBackground);
            }
        }
    }

    savePng("main.png", image);

    return EXIT_SUCCESS;
}