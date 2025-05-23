#include "raster_renderer.h"
#include <iostream>

void RasterRenderer::renderCircle(float radius) {
    std::cout << "Drawing circle as raster with radius: " << radius << std::endl;
}

void RasterRenderer::renderRectangle(float width, float height) {
    std::cout << "Drawing rectangle as raster with width: " << width << ", height: " << height << std::endl;
} 