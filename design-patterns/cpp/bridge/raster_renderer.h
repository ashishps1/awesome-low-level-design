#pragma once
#include "renderer.h"

class RasterRenderer : public Renderer {
public:
    void renderCircle(float radius) override;
    void renderRectangle(float width, float height) override;
}; 