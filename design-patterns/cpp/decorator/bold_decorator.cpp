#include "bold_decorator.h"
#include <iostream>

BoldDecorator::BoldDecorator(TextView* inner) : TextDecorator(inner) {}

void BoldDecorator::render() {
    std::cout << "<b>";
    inner->render();
    std::cout << "</b>";
} 