#pragma once
#include "text_decorator.h"

class UnderlineDecorator : public TextDecorator {
public:
    explicit UnderlineDecorator(TextView* inner);
    void render() override;
}; 