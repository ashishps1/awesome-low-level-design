from .http_request import HttpRequest


def http_app_builder_demo():
    """Demonstrate Builder pattern usage"""
    print("=== Builder Pattern Demo ===")
    
    # Example 1: Simple GET request
    get_request = (HttpRequest.Builder("https://api.example.com/users")
                   .method("GET")
                   .header("Accept", "application/json")
                   .timeout(5000)
                   .build())
    print(f"GET Request: {get_request}")
    
    # Example 2: POST request with body and custom headers
    post_request = (HttpRequest.Builder("https://api.example.com/posts")
                    .method("POST")
                    .header("Content-Type", "application/json")
                    .header("X-Auth-Token", "some_secret_token")
                    .body('{"title":"New Post","content":"Hello Builder!"}')
                    .query_param("userId", "123")
                    .build())
    print(f"POST Request: {post_request}")
    
    # Example 3: Request with only required URL (defaults for others)
    default_request = HttpRequest.Builder("https://api.example.com/status").build()
    print(f"Default Request: {default_request}")
    
    # Example 4: Illustrating potential warning from builder
    put_no_body_request = (HttpRequest.Builder("https://api.example.com/resource/1")
                          .method("PUT")
                          # .body("updated data")  # Body intentionally omitted
                          .build())
    print(f"PUT Request (no body): {put_no_body_request}")
    
    # Example of trying to build with invalid required parameter
    try:
        invalid_request = HttpRequest.Builder("").build()
    except ValueError as e:
        print(f"Error creating request: {e}")


if __name__ == "__main__":
    http_app_builder_demo()