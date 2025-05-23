#pragma once
#include "base_handler.h"
#include <iostream>

class BusinessLogicHandler : public BaseHandler {
public:
    void handle(Request& request) override {
        std::cout << "BusinessLogicHandler: 🚀 Processing request..." << std::endl;
        // Core application logic goes here
    }
}; 