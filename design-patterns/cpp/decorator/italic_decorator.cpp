#include "italic_decorator.h"
#include <iostream>

ItalicDecorator::ItalicDecorator(TextView* inner) : TextDecorator(inner) {}

void ItalicDecorator::render() {
    std::cout << "<i>";
    inner->render();
    std::cout << "</i>";
} 