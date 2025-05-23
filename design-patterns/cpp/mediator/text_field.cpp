#include "text_field.h"
#include <iostream>

TextField::TextField(UIMediator* mediator) : UIComponent(mediator) {}

void TextField::setText(const std::string& newText) {
    text = newText;
    std::cout << "TextField updated: " << newText << std::endl;
    notifyMediator();
}

const std::string& TextField::getText() const {
    return text;
} 