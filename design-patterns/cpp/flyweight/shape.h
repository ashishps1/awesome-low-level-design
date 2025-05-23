#pragma once
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() = 0;
}; 