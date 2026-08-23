#pragma once

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(double width, double height);

    double getWidth() const;
    double getHeight() const;
    void accept(ShapeVisitor* visitor) override;

private:
    double width;
    double height;
};