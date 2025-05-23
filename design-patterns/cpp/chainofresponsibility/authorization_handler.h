#pragma once
#include "base_handler.h"
#include <iostream>

class AuthorizationHandler : public BaseHandler {
public:
    void handle(Request& request) override {
        if (request.userRole != "ADMIN") {
            std::cout << "AuthorizationHandler: ❌ Access denied." << std::endl;
            return;
        }
        std::cout << "AuthorizationHandler: ✅ Authorized." << std::endl;
        forward(request);
    }
}; 