#pragma once
#include <string>

class Request {
public:
    std::string user;
    std::string userRole;
    int requestCount;
    std::string payload;

    Request(const std::string& user, const std::string& role, int requestCount, const std::string& payload);
}; 