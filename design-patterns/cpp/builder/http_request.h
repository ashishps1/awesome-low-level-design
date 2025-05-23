#pragma once
#include <string>
#include <map>
#include <iostream>

class HttpRequest {
public:
    class Builder;

    std::string getUrl() const;
    std::string getMethod() const;
    const std::map<std::string, std::string>& getHeaders() const;
    const std::map<std::string, std::string>& getQueryParams() const;
    std::string getBody() const;
    int getTimeout() const;

    friend std::ostream& operator<<(std::ostream& os, const HttpRequest& req);

private:
    std::string url;
    std::string method;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> queryParams;
    std::string body;
    int timeout;

    HttpRequest(const Builder& builder);
}; 