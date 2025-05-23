#pragma once
#include "renderer.h"

class VectorRenderer : public Renderer {
public:
    void renderCircle(float radius) override;
    void renderRectangle(float width, float height) override;
}; 