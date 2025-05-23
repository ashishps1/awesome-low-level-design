#include "button.h"
#include <iostream>

Button::Button(UIMediator* mediator) : UIComponent(mediator), enabled(false) {}

void Button::click() {
    if (enabled) {
        std::cout << "Login Button clicked!" << std::endl;
        notifyMediator(); // Will trigger login attempt
    } else {
        std::cout << "Login Button is disabled." << std::endl;
    }
}

void Button::setEnabled(bool value) {
    enabled = value;
    std::cout << "Login Button is now " << (enabled ? "ENABLED" : "DISABLED") << std::endl;
} 