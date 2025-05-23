#include "circle.h"
#include <iostream>

Circle::Circle(const std::string& color) : color(color) {}

void Circle::draw() {
    std::cout << "Drawing Circle[ color: " << color 
              << ", x: " << x 
              << ", y: " << y 
              << ", radius: " << radius 
              << " ]" << std::endl;
} 