#include "shape_factory.h"
#include "circle.h"

std::unordered_map<std::string, Shape*> ShapeFactory::circleMap;

Shape* ShapeFactory::getCircle(const std::string& color) {
    auto it = circleMap.find(color);
    if (it == circleMap.end()) {
        Circle* circle = new Circle(color);
        circleMap[color] = circle;
        std::cout << "Creating circle of color: " << color << std::endl;
        return circle;
    }
    return it->second;
}

int ShapeFactory::getCircleCount() {
    return circleMap.size();
} 