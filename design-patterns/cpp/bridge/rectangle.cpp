#include "rectangle.h"

Rectangle::Rectangle(Renderer* renderer, float width, float height)
    : Shape(renderer), width(width), height(height) {}

void Rectangle::draw() {
    renderer->renderRectangle(width, height);
} 