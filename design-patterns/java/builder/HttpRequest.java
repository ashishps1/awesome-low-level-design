import java.util.HashMap;
import java.util.Map;
import java.util.Collections;

public class HttpRequest {
    private final String url;         // Required
    private final String method;      // Optional, default GET
    private final Map<String, String> headers; // Optional
    private final Map<String, String> queryParams; // Optional
    private final String body;        // Optional
    private final int timeout;        // Optional, default 30s

    // Private constructor, only accessible by the Builder
    private HttpRequest(Builder builder) {
        this.url = builder.url;
        this.method = builder.method;
        this.headers = Collections.unmodifiableMap(new HashMap<>(builder.headers)); // Defensive copy
        this.queryParams = Collections.unmodifiableMap(new HashMap<>(builder.queryParams)); // Defensive copy
        this.body = builder.body;
        this.timeout = builder.timeout;
    }

    // Getters (no setters to ensure immutability)
    public String getUrl() { return url; }
    public String getMethod() { return method; }
    public Map<String, String> getHeaders() { return headers; }
    public Map<String, String> getQueryParams() { return queryParams; }
    public String getBody() { return body; }
    public int getTimeout() { return timeout; }

    @Override
    public String toString() {
        return "HttpRequest{" +
               "url='" + url + '\'' +
               ", method='" + method + '\'' +
               ", headers=" + headers +
               ", queryParams=" + queryParams +
               ", body='" + (body != null ? body.substring(0, Math.min(10, body.length()))+"..." : "null") + '\'' +
               ", timeout=" + timeout +
               '}';
    }

    // --- Static Nested Builder Class ---
    public static class Builder {
        // Required parameter
        private final String url;

        // Optional parameters - initialized to default values
        private String method = "GET";
        private Map<String, String> headers = new HashMap<>();
        private Map<String, String> queryParams = new HashMap<>();
        private String body = null;
        private int timeout = 30000; // 30 seconds default

        // Builder constructor for required fields
        public Builder(String url) {
            if (url == null || url.trim().isEmpty()) {
                throw new IllegalArgumentException("URL cannot be null or empty.");
            }
            this.url = url;
        }

        // Setter-like methods for optional fields, returning the Builder for fluency
        public Builder method(String method) {
            this.method = (method == null || method.trim().isEmpty()) ? "GET" : method.toUpperCase();
            return this;
        }

        public Builder header(String key, String value) {
            if (key != null && value != null) {
                this.headers.put(key, value);
            }
            return this;
        }

        public Builder queryParam(String key, String value) {
            if (key != null && value != null) {
                this.queryParams.put(key, value);
            }
            return this;
        }

        public Builder body(String body) {
            this.body = body;
            return this;
        }

        public Builder timeout(int timeoutMillis) {
            if (timeoutMillis > 0) {
                this.timeout = timeoutMillis;
            }
            return this;
        }

        // The final build method that creates the HttpRequest object
        public HttpRequest build() {
            // Optionally, add validation logic here before creating the object
            // For example, ensure body is present for POST/PUT if required by your design
            if (("POST".equals(method) || "PUT".equals(method)) && (body == null || body.isEmpty())) {
                 System.out.println("Warning: Building " + method + " request without a body for URL: " + url);
            }
            return new HttpRequest(this);
        }
    }    
}
