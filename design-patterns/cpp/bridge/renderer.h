#pragma once

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void renderCircle(float radius) = 0;
    virtual void renderRectangle(float width, float height) = 0;
}; 