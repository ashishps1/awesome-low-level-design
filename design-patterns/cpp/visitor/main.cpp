#include "circle.h"
#include "rectangle.h"
#include "shape_visitor.h"

#include <iostream>

class ShapeDetailsVisitor : public ShapeVisitor {
public:
    void visitCircle(Circle* circle) override {
        std::cout << "Circle radius: " << circle->getRadius() << '\n';
    }

    void visitRectangle(Rectangle* rectangle) override {
        std::cout << "Rectangle width: " << rectangle->getWidth()
                  << ", height: " << rectangle->getHeight() << '\n';
    }
};

int main() {
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);
    ShapeDetailsVisitor visitor;

    circle.accept(&visitor);
    rectangle.accept(&visitor);
}