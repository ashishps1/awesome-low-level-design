#pragma once

class ShapeVisitor;

class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(ShapeVisitor* visitor) = 0;
};