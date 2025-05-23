#pragma once
#include "shape.h"
#include <unordered_map>
#include <string>
#include <memory>

class ShapeFactory {
public:
    static Shape* getCircle(const std::string& color);
    static int getCircleCount();

private:
    static std::unordered_map<std::string, Shape*> circleMap;
}; 