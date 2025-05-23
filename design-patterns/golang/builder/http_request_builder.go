package builder

import (
	"fmt"
	"strings"
)

// HttpRequestBuilder is responsible for building HttpRequest objects
type HttpRequestBuilder struct {
	url         string            // Required
	method      string            // Optional, default GET
	headers     map[string]string // Optional
	queryParams map[string]string // Optional
	body        string            // Optional
	timeout     int               // Optional, default 30s
}

// NewHttpRequestBuilder creates a new HttpRequestBuilder with the required URL
func NewHttpRequestBuilder(url string) (*HttpRequestBuilder, error) {
	if strings.TrimSpace(url) == "" {
		return nil, fmt.Errorf("URL cannot be null or empty")
	}

	return &HttpRequestBuilder{
		url:         url,
		method:      "GET",
		headers:     make(map[string]string),
		queryParams: make(map[string]string),
		timeout:     30000, // 30 seconds default
	}, nil
}

// Method sets the HTTP method
func (b *HttpRequestBuilder) Method(method string) *HttpRequestBuilder {
	if strings.TrimSpace(method) == "" {
		b.method = "GET"
	} else {
		b.method = strings.ToUpper(method)
	}
	return b
}

// Header adds a header to the request
func (b *HttpRequestBuilder) Header(key, value string) *HttpRequestBuilder {
	if key != "" && value != "" {
		b.headers[key] = value
	}
	return b
}

// QueryParam adds a query parameter to the request
func (b *HttpRequestBuilder) QueryParam(key, value string) *HttpRequestBuilder {
	if key != "" && value != "" {
		b.queryParams[key] = value
	}
	return b
}

// Body sets the request body
func (b *HttpRequestBuilder) Body(body string) *HttpRequestBuilder {
	b.body = body
	return b
}

// Timeout sets the request timeout in milliseconds
func (b *HttpRequestBuilder) Timeout(timeoutMillis int) *HttpRequestBuilder {
	if timeoutMillis > 0 {
		b.timeout = timeoutMillis
	}
	return b
}

// Build creates and returns a new HttpRequest
func (b *HttpRequestBuilder) Build() *HttpRequest {
	// Validate the request
	if (b.method == "POST" || b.method == "PUT") && b.body == "" {
		fmt.Printf("Warning: Building %s request without a body for URL: %s\n", b.method, b.url)
	}

	return NewHttpRequest(b)
}
