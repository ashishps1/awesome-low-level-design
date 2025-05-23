#include "ui_component.h"

UIComponent::UIComponent(UIMediator* mediator) : mediator(mediator) {}

void UIComponent::notifyMediator() {
    mediator->componentChanged(this);
} 