#pragma once
#include "ui_component.h"

class Button : public UIComponent {
public:
    explicit Button(UIMediator* mediator);
    void click();
    void setEnabled(bool value);

private:
    bool enabled;
}; 