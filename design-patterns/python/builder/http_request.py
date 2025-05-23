from typing import Dict, Optional


class HttpRequest:
    """Immutable HttpRequest object created using Builder pattern"""
    
    def __init__(self, builder):
        """Private constructor - only accessible by Builder"""
        self._url = builder._url
        self._method = builder._method
        self._headers = dict(builder._headers)  # Defensive copy
        self._query_params = dict(builder._query_params)  # Defensive copy
        self._body = builder._body
        self._timeout = builder._timeout
    
    # Getters (no setters to ensure immutability)
    @property
    def url(self) -> str:
        return self._url
    
    @property
    def method(self) -> str:
        return self._method
    
    @property
    def headers(self) -> Dict[str, str]:
        return self._headers.copy()  # Return copy to maintain immutability
    
    @property
    def query_params(self) -> Dict[str, str]:
        return self._query_params.copy()  # Return copy to maintain immutability
    
    @property
    def body(self) -> Optional[str]:
        return self._body
    
    @property
    def timeout(self) -> int:
        return self._timeout
    
    def __str__(self) -> str:
        body_preview = None
        if self._body:
            body_preview = self._body[:10] + "..." if len(self._body) > 10 else self._body
        
        return (f"HttpRequest(url='{self._url}', method='{self._method}', "
                f"headers={self._headers}, query_params={self._query_params}, "
                f"body='{body_preview}', timeout={self._timeout})")
    
    class Builder:
        """Static nested Builder class for fluent API"""
        
        def __init__(self, url: str):
            """Builder constructor for required fields"""
            if not url or not url.strip():
                raise ValueError("URL cannot be null or empty")
            
            self._url = url
            # Optional parameters with default values
            self._method = "GET"
            self._headers = {}
            self._query_params = {}
            self._body = None
            self._timeout = 30000  # 30 seconds default
        
        def method(self, method: str) -> 'HttpRequest.Builder':
            """Set HTTP method"""
            self._method = method.upper() if method and method.strip() else "GET"
            return self
        
        def header(self, key: str, value: str) -> 'HttpRequest.Builder':
            """Add header"""
            if key and value:
                self._headers[key] = value
            return self
        
        def query_param(self, key: str, value: str) -> 'HttpRequest.Builder':
            """Add query parameter"""
            if key and value:
                self._query_params[key] = value
            return self
        
        def body(self, body: str) -> 'HttpRequest.Builder':
            """Set request body"""
            self._body = body
            return self
        
        def timeout(self, timeout_millis: int) -> 'HttpRequest.Builder':
            """Set timeout in milliseconds"""
            if timeout_millis > 0:
                self._timeout = timeout_millis
            return self
        
        def build(self) -> 'HttpRequest':
            """Build the final HttpRequest object"""
            # Validation logic
            if self._method in ["POST", "PUT"] and (not self._body or not self._body.strip()):
                print(f"Warning: Building {self._method} request without a body for URL: {self._url}")
            
            return HttpRequest(self)