#pragma once
#include "text_decorator.h"

class ItalicDecorator : public TextDecorator {
public:
    explicit ItalicDecorator(TextView* inner);
    void render() override;
}; 