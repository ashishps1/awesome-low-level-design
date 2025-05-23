#include "form_mediator.h"
#include "text_field.h"
#include "button.h"
#include "label.h"
#include <iostream>

int main() {
    // Create the mediator
    FormMediator mediator;

    // Create UI components
    TextField usernameField(&mediator);
    TextField passwordField(&mediator);
    Button loginButton(&mediator);
    Label statusLabel(&mediator);

    // Register components with the mediator
    mediator.setUsernameField(&usernameField);
    mediator.setPasswordField(&passwordField);
    mediator.setLoginButton(&loginButton);
    mediator.setStatusLabel(&statusLabel);

    std::cout << "=== Login Form Demo ===\n" << std::endl;

    // Test with empty fields
    std::cout << "Test 1: Empty fields" << std::endl;
    loginButton.click();

    // Test with username only
    std::cout << "\nTest 2: Username only" << std::endl;
    usernameField.setText("admin");
    loginButton.click();

    // Test with both fields
    std::cout << "\nTest 3: Both fields filled" << std::endl;
    passwordField.setText("1234");
    loginButton.click();

    // Test with wrong credentials
    std::cout << "\nTest 4: Wrong credentials" << std::endl;
    usernameField.setText("user");
    passwordField.setText("pass");
    loginButton.click();

    return 0;
} 