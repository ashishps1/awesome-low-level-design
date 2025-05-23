#include "http_request.h"
#include "http_request_builder.h"
#include <iostream>

int main() {
    // Example 1: Simple GET request
    HttpRequest getRequest = HttpRequest::Builder("https://api.example.com/users")
                                .method("GET")
                                .header("Accept", "application/json")
                                .timeout(5000)
                                .build();
    std::cout << "GET Request: " << getRequest << std::endl;

    // Example 2: POST request with body and custom headers
    HttpRequest postRequest = HttpRequest::Builder("https://api.example.com/posts")
                                 .method("POST")
                                 .header("Content-Type", "application/json")
                                 .header("X-Auth-Token", "some_secret_token")
                                 .body("{\"title\":\"New Post\",\"content\":\"Hello Builder!\"}")
                                 .queryParam("userId", "123")
                                 .build();
    std::cout << "POST Request: " << postRequest << std::endl;

    // Example 3: Request with only required URL (defaults for others)
    HttpRequest defaultRequest = HttpRequest::Builder("https://api.example.com/status").build();
    std::cout << "Default Request: " << defaultRequest << std::endl;

    // Example 4: Illustrating potential warning from builder
    HttpRequest putNoBodyRequest = HttpRequest::Builder("https://api.example.com/resource/1")
                                        .method("PUT")
                                        // .body("updated data") // Body intentionally omitted
                                        .build();
    std::cout << "PUT Request (no body): " << putNoBodyRequest << std::endl;

    // Example of trying to build with invalid required parameter
    try {
        HttpRequest invalidRequest = HttpRequest::Builder("").build();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error creating request: " << e.what() << std::endl;
    }
} 