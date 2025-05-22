public class HttpAppBuilder {
    public static void main(String[] args) {
        // Example 1: Simple GET request
        HttpRequest getRequest = new HttpRequest.Builder("https://api.example.com/users")
                                        .method("GET")
                                        .header("Accept", "application/json")
                                        .timeout(5000)
                                        .build();
        System.out.println("GET Request: " + getRequest);

        // Example 2: POST request with body and custom headers
        HttpRequest postRequest = new HttpRequest.Builder("https://api.example.com/posts")
                                         .method("POST")
                                         .header("Content-Type", "application/json")
                                         .header("X-Auth-Token", "some_secret_token")
                                         .body("{\"title\":\"New Post\",\"content\":\"Hello Builder!\"}")
                                         .queryParam("userId", "123")
                                         .build();
        System.out.println("POST Request: " + postRequest);

        // Example 3: Request with only required URL (defaults for others)
        HttpRequest defaultRequest = new HttpRequest.Builder("https://api.example.com/status").build();
        System.out.println("Default Request: " + defaultRequest);

        // Example 4: Illustrating potential warning from builder
        HttpRequest putNoBodyRequest = new HttpRequest.Builder("https://api.example.com/resource/1")
                                            .method("PUT")
                                            // .body("updated data") // Body intentionally omitted
                                            .build();
        System.out.println("PUT Request (no body): " + putNoBodyRequest);

        // Example of trying to build with invalid required parameter
        try {
            HttpRequest invalidRequest = new HttpRequest.Builder(null).build();
        } catch (IllegalArgumentException e) {
            System.err.println("Error creating request: " + e.getMessage());
        }
    }    
}
