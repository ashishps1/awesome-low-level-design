#include "plain_text_view.h"
#include "bold_decorator.h"
#include "italic_decorator.h"
#include "underline_decorator.h"
#include <iostream>

int main() {
    TextView* plain = new PlainTextView("Hello, world!");

    std::cout << "Plain: ";
    plain->render();
    std::cout << std::endl;

    std::cout << "Bold: ";
    TextView* bold = new BoldDecorator(plain);
    bold->render();
    std::cout << std::endl;

    std::cout << "Italic + Bold: ";
    TextView* italicBold = new ItalicDecorator(bold);
    italicBold->render();
    std::cout << std::endl;

    std::cout << "Underline + Italic + Bold: ";
    TextView* fullStyle = new UnderlineDecorator(italicBold);
    fullStyle->render();
    std::cout << std::endl;

    // Clean up
    delete fullStyle;
    delete italicBold;
    delete bold;
    delete plain;
    return 0;
} 