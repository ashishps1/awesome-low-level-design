#pragma once
#include "shape.h"

class Circle : public Shape {
public:
    Circle(Renderer* renderer, float radius);
    void draw() override;
private:
    float radius;
}; 