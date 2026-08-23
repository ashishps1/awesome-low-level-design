#include "rectangle.h"

#include "shape_visitor.h"

Rectangle::Rectangle(double width, double height) : width(width), height(height) {}

double Rectangle::getWidth() const {
    return width;
}

double Rectangle::getHeight() const {
    return height;
}

void Rectangle::accept(ShapeVisitor* visitor) {
    visitor->visitRectangle(this);
}