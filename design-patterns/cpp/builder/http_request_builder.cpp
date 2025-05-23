#include "http_request_builder.h"
#include <iostream>
#include <algorithm>

HttpRequest::Builder::Builder(const std::string& url) : url(url) {
    if (url.empty()) {
        throw std::invalid_argument("URL cannot be empty.");
    }
}

HttpRequest::Builder& HttpRequest::Builder::method(const std::string& m) {
    method = m.empty() ? "GET" : m;
    std::transform(method.begin(), method.end(), method.begin(), ::toupper);
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::header(const std::string& key, const std::string& value) {
    if (!key.empty() && !value.empty()) headers[key] = value;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::queryParam(const std::string& key, const std::string& value) {
    if (!key.empty() && !value.empty()) queryParams[key] = value;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::body(const std::string& b) {
    body = b;
    return *this;
}

HttpRequest::Builder& HttpRequest::Builder::timeout(int timeoutMillis) {
    if (timeoutMillis > 0) timeout = timeoutMillis;
    return *this;
}

HttpRequest HttpRequest::Builder::build() {
    if ((method == "POST" || method == "PUT") && body.empty()) {
        std::cout << "Warning: Building " << method << " request without a body for URL: " << url << std::endl;
    }
    return HttpRequest(*this);
} 