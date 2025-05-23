#include "request.h"

Request::Request(const std::string& user, const std::string& role, int requestCount, const std::string& payload)
    : user(user), userRole(role), requestCount(requestCount), payload(payload) {} 