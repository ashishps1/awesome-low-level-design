public class HttpAppTelescoping {
    public static void main(String[] args) {
        HttpRequestTelescoping req1 = new HttpRequestTelescoping("https://api.example.com/data"); // GET, defaults
        HttpRequestTelescoping req2 = new HttpRequestTelescoping("https://api.example.com/submit", "POST", null, null, "{\"key\":\"value\"}"); // POST with body
        HttpRequestTelescoping req3 = new HttpRequestTelescoping("https://api.example.com/config", "PUT", Map.of("X-API-Key", "secret"), null, "config_data", 5000);
    }    
}
