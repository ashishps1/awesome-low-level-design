#include "circle.h"

Circle::Circle(Renderer* renderer, float radius)
    : Shape(renderer), radius(radius) {}

void Circle::draw() {
    renderer->renderCircle(radius);
} 