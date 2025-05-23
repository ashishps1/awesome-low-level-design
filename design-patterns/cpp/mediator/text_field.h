#pragma once
#include "ui_component.h"
#include <string>

class TextField : public UIComponent {
public:
    explicit TextField(UIMediator* mediator);
    void setText(const std::string& newText);
    const std::string& getText() const;

private:
    std::string text;
}; 