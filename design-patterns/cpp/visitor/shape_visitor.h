#pragma once

class Circle;
class Rectangle;

class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visitCircle(Circle* circle) = 0;
    virtual void visitRectangle(Rectangle* rectangle) = 0;
};