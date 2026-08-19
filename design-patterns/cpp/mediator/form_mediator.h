git add design-patterns/cpp/mediator/form_mediator.h design-patterns/cpp/mediator/form_mediator.cpp
#pragma once
#include "ui_mediator.h"

class TextField;
class Button;
class Label;

class FormMediator : public UIMediator {
public:
    void setUsernameField(TextField* field);
    void setPasswordField(TextField* field);
    void setLoginButton(Button* button);
    void setStatusLabel(Label* label);
    void componentChanged(UIComponent* component) override;

private:
    TextField* usernameField = nullptr;
    TextField* passwordField = nullptr;
    Button* loginButton = nullptr;
    Label* statusLabel = nullptr;
}; 