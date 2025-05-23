#pragma once
#include "base_handler.h"
#include <iostream>

class RateLimitHandler : public BaseHandler {
public:
    void handle(Request& request) override {
        if (request.requestCount >= 100) {
            std::cout << "RateLimitHandler: ❌ Rate limit exceeded." << std::endl;
            return;
        }
        std::cout << "RateLimitHandler: ✅ Within rate limit." << std::endl;
        forward(request);
    }
}; 