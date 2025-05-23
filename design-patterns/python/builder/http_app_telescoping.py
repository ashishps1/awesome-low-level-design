from .http_request_telescoping import HttpRequestTelescoping


def http_app_telescoping_demo():
    """Demonstrate telescoping constructor anti-pattern"""
    print("=== Telescoping Constructor Anti-Pattern Demo ===")
    
    # Example 1: GET request with defaults
    req1 = HttpRequestTelescoping.with_url("https://api.example.com/data")
    
    # Example 2: POST with body (have to pass None for intermediate parameters)
    req2 = HttpRequestTelescoping("https://api.example.com/submit", "POST", None, None, '{"key":"value"}')
    
    # Example 3: Complex request with all parameters
    req3 = HttpRequestTelescoping(
        "https://api.example.com/config",
        "PUT",
        {"X-API-Key": "secret"},
        {"version": "v1"},
        "config_data",
        5000
    )
    
    print("All requests created using telescoping constructors")


if __name__ == "__main__":
    http_app_telescoping_demo()