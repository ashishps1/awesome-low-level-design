#pragma once
#include "ui_mediator.h"

class UIComponent {
public:
    explicit UIComponent(UIMediator* mediator);
    virtual ~UIComponent() = default;

protected:
    void notifyMediator();
    UIMediator* mediator;
}; 