package builder

import (
	"fmt"
)

// HttpRequest represents an HTTP request with all its components
type HttpRequest struct {
	url         string            // Required
	method      string            // Optional, default GET
	headers     map[string]string // Optional
	queryParams map[string]string // Optional
	body        string            // Optional
	timeout     int               // Optional, default 30s
}

// NewHttpRequest creates a new HttpRequest using the builder pattern
func NewHttpRequest(builder *HttpRequestBuilder) *HttpRequest {
	return &HttpRequest{
		url:         builder.url,
		method:      builder.method,
		headers:     builder.headers,
		queryParams: builder.queryParams,
		body:        builder.body,
		timeout:     builder.timeout,
	}
}

// GetURL returns the request URL
func (r *HttpRequest) GetURL() string {
	return r.url
}

// GetMethod returns the request method
func (r *HttpRequest) GetMethod() string {
	return r.method
}

// GetHeaders returns the request headers
func (r *HttpRequest) GetHeaders() map[string]string {
	return r.headers
}

// GetQueryParams returns the request query parameters
func (r *HttpRequest) GetQueryParams() map[string]string {
	return r.queryParams
}

// GetBody returns the request body
func (r *HttpRequest) GetBody() string {
	return r.body
}

// GetTimeout returns the request timeout
func (r *HttpRequest) GetTimeout() int {
	return r.timeout
}

// String returns a string representation of the HttpRequest
func (r *HttpRequest) String() string {
	bodyPreview := r.body
	if len(bodyPreview) > 10 {
		bodyPreview = bodyPreview[:10] + "..."
	}
	return fmt.Sprintf("HttpRequest{url='%s', method='%s', headers=%v, queryParams=%v, body='%s', timeout=%d}",
		r.url, r.method, r.headers, r.queryParams, bodyPreview, r.timeout)
}
