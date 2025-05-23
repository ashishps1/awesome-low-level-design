#pragma once
#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(Renderer* renderer, float width, float height);
    void draw() override;
private:
    float width;
    float height;
}; 