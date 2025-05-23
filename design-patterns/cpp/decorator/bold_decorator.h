#pragma once
#include "text_decorator.h"

class BoldDecorator : public TextDecorator {
public:
    explicit BoldDecorator(TextView* inner);
    void render() override;
}; 