#include "vector_renderer.h"
#include "raster_renderer.h"
#include "circle.h"
#include "rectangle.h"
#include <iostream>

int main() {
    VectorRenderer vectorRenderer;
    RasterRenderer rasterRenderer;

    Circle vectorCircle(&vectorRenderer, 5.0f);
    Rectangle vectorRectangle(&vectorRenderer, 4.0f, 3.0f);

    Circle rasterCircle(&rasterRenderer, 7.0f);
    Rectangle rasterRectangle(&rasterRenderer, 6.0f, 2.0f);

    std::cout << "Vector Circle: ";
    vectorCircle.draw();
    std::cout << "Vector Rectangle: ";
    vectorRectangle.draw();
    std::cout << "Raster Circle: ";
    rasterCircle.draw();
    std::cout << "Raster Rectangle: ";
    rasterRectangle.draw();

    return 0;
} 