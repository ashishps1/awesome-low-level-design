#pragma once
#include "ui_mediator.h"
#include "text_field.h"
#include "button.h"
#include "label.h"

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