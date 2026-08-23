#include "circle.h"

#include "shape_visitor.h"

Circle::Circle(double radius) : radius(radius) {}

double Circle::getRadius() const {
    return radius;
}

void Circle::accept(ShapeVisitor* visitor) {
    visitor->visitCircle(this);
}