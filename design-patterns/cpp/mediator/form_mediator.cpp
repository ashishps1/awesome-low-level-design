#include "form_mediator.h"
#include <iostream>

void FormMediator::setUsernameField(TextField* field) {
    usernameField = field;
}

void FormMediator::setPasswordField(TextField* field) {
    passwordField = field;
}

void FormMediator::setLoginButton(Button* button) {
    loginButton = button;
}

void FormMediator::setStatusLabel(Label* label) {
    statusLabel = label;
}

void FormMediator::componentChanged(UIComponent* component) {
    if (component == usernameField || component == passwordField) {
        bool enableButton = !usernameField->getText().empty() && !passwordField->getText().empty();
        loginButton->setEnabled(enableButton);
    } else if (component == loginButton) {
        const std::string& username = usernameField->getText();
        const std::string& password = passwordField->getText();

        if (username == "admin" && password == "1234") {
            statusLabel->setText("✅ Login successful!");
        } else {
            statusLabel->setText("❌ Invalid credentials.");
        }
    }
} 