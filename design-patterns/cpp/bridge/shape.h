#pragma once
#include "renderer.h"

class Shape {
protected:
    Renderer* renderer;
public:
    explicit Shape(Renderer* renderer);
    virtual ~Shape() = default;
    virtual void draw() = 0;
}; 