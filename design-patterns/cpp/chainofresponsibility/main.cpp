#include "auth_handler.h"
#include "authorization_handler.h"
#include "rate_limit_handler.h"
#include "validation_handler.h"
#include "business_logic_handler.h"
#include "request.h"
#include <iostream>

int main() {
    // Create handlers
    AuthHandler auth;
    AuthorizationHandler authorization;
    RateLimitHandler rateLimit;
    ValidationHandler validation;
    BusinessLogicHandler businessLogic;

    // Build the chain
    auth.setNext(&authorization);
    authorization.setNext(&rateLimit);
    rateLimit.setNext(&validation);
    validation.setNext(&businessLogic);

    // Send a request through the chain
    Request request("john", "ADMIN", 10, "{ \"data\": \"valid\" }");
    auth.handle(request);

    std::cout << "\n--- Trying an invalid request ---" << std::endl;
    Request badRequest("", "USER", 150, "");
    auth.handle(badRequest);

    return 0;
} 