#pragma once

#include "shape.h"

class Circle : public Shape {
public:
    explicit Circle(double radius);

    double getRadius() const;
    void accept(ShapeVisitor* visitor) override;

private:
    double radius;
};