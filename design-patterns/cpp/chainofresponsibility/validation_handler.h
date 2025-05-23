#pragma once
#include "base_handler.h"
#include <iostream>

class ValidationHandler : public BaseHandler {
public:
    void handle(Request& request) override {
        if (request.payload.empty() || request.payload.find_first_not_of(" \t\n\r") == std::string::npos) {
            std::cout << "ValidationHandler: ❌ Invalid payload." << std::endl;
            return;
        }
        std::cout << "ValidationHandler: ✅ Payload valid." << std::endl;
        forward(request);
    }
}; 