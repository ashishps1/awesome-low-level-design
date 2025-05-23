#pragma once
#include "shape.h"
#include <string>

class Circle : public Shape {
public:
    Circle(const std::string& color);
    void draw() override;

private:
    std::string color;
    int x = 0;
    int y = 0;
    int radius = 0;
}; 