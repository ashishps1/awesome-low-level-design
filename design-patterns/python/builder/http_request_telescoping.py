from typing import Dict, Optional


class HttpRequestTelescoping:
    """Telescoping constructor anti-pattern example"""
    
    def __init__(self, url: str, method: str = "GET", headers: Optional[Dict[str, str]] = None,
                 query_params: Optional[Dict[str, str]] = None, body: Optional[str] = None,
                 timeout: int = 30000):
        """All-parameter constructor (telescoping pattern)"""
        self.url = url
        self.method = method
        self.headers = headers if headers is not None else {}
        self.query_params = query_params if query_params is not None else {}
        self.body = body
        self.timeout = timeout
        
        print(f"HttpRequest Created: URL={url}, Method={method}, "
              f"Headers={len(self.headers)}, Params={len(self.query_params)}, "
              f"Body={body is not None}, Timeout={timeout}")
    
    # Additional constructors to simulate Java's telescoping pattern
    @classmethod
    def with_url(cls, url: str) -> 'HttpRequestTelescoping':
        """Constructor with only URL"""
        return cls(url)
    
    @classmethod
    def with_url_and_method(cls, url: str, method: str) -> 'HttpRequestTelescoping':
        """Constructor with URL and method"""
        return cls(url, method)
    
    @classmethod
    def with_headers(cls, url: str, method: str, headers: Dict[str, str]) -> 'HttpRequestTelescoping':
        """Constructor with URL, method, and headers"""
        return cls(url, method, headers)
    
    @classmethod
    def with_query_params(cls, url: str, method: str, headers: Optional[Dict[str, str]],
                         query_params: Dict[str, str]) -> 'HttpRequestTelescoping':
        """Constructor with URL, method, headers, and query params"""
        return cls(url, method, headers, query_params)
    
    @classmethod
    def with_body(cls, url: str, method: str, headers: Optional[Dict[str, str]],
                  query_params: Optional[Dict[str, str]], body: str) -> 'HttpRequestTelescoping':
        """Constructor with URL, method, headers, query params, and body"""
        return cls(url, method, headers, query_params, body)