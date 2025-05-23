#pragma once
#include "text_view.h"

class TextDecorator : public TextView {
protected:
    TextView* inner;
public:
    explicit TextDecorator(TextView* inner);
}; 