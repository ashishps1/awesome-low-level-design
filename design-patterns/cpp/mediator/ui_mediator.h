#pragma once

// Forward declaration
class UIComponent;

class UIMediator {
public:
    virtual ~UIMediator() = default;
    virtual void componentChanged(UIComponent* component) = 0;
}; 