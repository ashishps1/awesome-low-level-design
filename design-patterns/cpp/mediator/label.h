#pragma once
#include "ui_component.h"
#include <string>

class Label : public UIComponent {
public:
    explicit Label(UIMediator* mediator);
    void setText(const std::string& message);

private:
    std::string text;
}; 