#include "underline_decorator.h"
#include <iostream>

UnderlineDecorator::UnderlineDecorator(TextView* inner) : TextDecorator(inner) {}

void UnderlineDecorator::render() {
    std::cout << "<u>";
    inner->render();
    std::cout << "</u>";
} 