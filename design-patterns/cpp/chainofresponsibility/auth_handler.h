#pragma once
#include "base_handler.h"
#include <iostream>

class AuthHandler : public BaseHandler {
public:
    void handle(Request& request) override {
        if (request.user.empty()) {
            std::cout << "AuthHandler: ❌ User not authenticated." << std::endl;
            return;
        }
        std::cout << "AuthHandler: ✅ Authenticated." << std::endl;
        forward(request);
    }
}; 