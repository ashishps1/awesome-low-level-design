#include "label.h"
#include <iostream>

Label::Label(UIMediator* mediator) : UIComponent(mediator) {}

void Label::setText(const std::string& message) {
    text = message;
    std::cout << "Status: " << text << std::endl;
} 