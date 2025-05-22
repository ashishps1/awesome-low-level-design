
import java.util.HashMap;
import java.util.Map;

public class HttpRequestTelescoping {
    private String url;         // Required
    private String method;      // Optional, default GET
    private Map<String, String> headers; // Optional
    private Map<String, String> queryParams; // Optional
    private String body;        // Optional
    private int timeout;        // Optional, default 30s

    public HttpRequestTelescoping(String url) {
        this(url, "GET");
    }
    public HttpRequestTelescoping(String url, String method) {
        this(url, method, null);
    }
    public HttpRequestTelescoping(String url, String method, Map<String, String> headers) {
        this(url, method, headers, null);
    }
    public HttpRequestTelescoping(String url, String method, Map<String, String> headers, Map<String, String> queryParams) {
        this(url, method, headers, queryParams, null);
    }
    public HttpRequestTelescoping(String url, String method, Map<String, String> headers, Map<String, String> queryParams, String body) {
        this(url, method, headers, queryParams, body, 30000);
    }
    public HttpRequestTelescoping(String url, String method, Map<String, String> headers,
                                  Map<String, String> queryParams, String body, int timeout) {
        this.url = url;
        this.method = method;
        this.headers = headers == null ? new HashMap<>() : headers;
        this.queryParams = queryParams == null ? new HashMap<>() : queryParams;
        this.body = body;
        this.timeout = timeout;
        System.out.println("HttpRequest Created: URL=" + url + ", Method=" + method +
                           ", Headers=" + this.headers.size() + ", Params=" + this.queryParams.size() +
                           ", Body=" + (body != null) + ", Timeout=" + timeout);
    }
    // ... getters ...    
}
