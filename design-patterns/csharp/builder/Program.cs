using System;

namespace Builder
{
    class Program
    {
        static void Main(string[] args)
        {
            // Example 1: Simple GET request
            var getRequest = new HttpRequest.Builder("https://api.example.com/users")
                .WithHeader("Accept", "application/json")
                .WithQueryParam("page", "1")
                .WithQueryParam("limit", "10")
                .Build();

            Console.WriteLine("=== GET Request ===");
            Console.WriteLine(getRequest);

            // Example 2: POST request with body
            var postRequest = new HttpRequest.Builder("https://api.example.com/users")
                .WithMethod("POST")
                .WithHeader("Content-Type", "application/json")
                .WithHeader("Authorization", "Bearer token123")
                .WithBody("{\"name\":\"John Doe\",\"email\":\"john@example.com\"}")
                .WithTimeout(5000)
                .Build();

            Console.WriteLine("\n=== POST Request ===");
            Console.WriteLine(postRequest);

            // Example 3: PUT request with validation warning
            var putRequest = new HttpRequest.Builder("https://api.example.com/users/123")
                .WithMethod("PUT")
                .WithHeader("Content-Type", "application/json")
                .WithHeader("Authorization", "Bearer token123")
                .WithTimeout(10000)
                .Build();

            Console.WriteLine("\n=== PUT Request (with warning) ===");
            Console.WriteLine(putRequest);
        }
    }
} 