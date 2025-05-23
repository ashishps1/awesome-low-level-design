#include "shape_factory.h"
#include <iostream>

int main() {
    std::cout << "Flyweight Pattern Demo\n" << std::endl;

    // Get circles of different colors
    Shape* redCircle = ShapeFactory::getCircle("Red");
    redCircle->draw();

    Shape* greenCircle = ShapeFactory::getCircle("Green");
    greenCircle->draw();

    Shape* blueCircle = ShapeFactory::getCircle("Blue");
    blueCircle->draw();

    // Try to get a red circle again
    Shape* redCircle2 = ShapeFactory::getCircle("Red");
    redCircle2->draw();

    std::cout << "\nTotal number of circle objects created: " 
              << ShapeFactory::getCircleCount() << std::endl;

    return 0;
} 