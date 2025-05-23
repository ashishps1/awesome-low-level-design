using System;
using System.Collections.Generic;
using System.Linq;

namespace Builder
{
    public class HttpRequest
    {
        public string Url { get; }         // Required
        public string Method { get; }      // Optional, default GET
        public IReadOnlyDictionary<string, string> Headers { get; } // Optional
        public IReadOnlyDictionary<string, string> QueryParams { get; } // Optional
        public string Body { get; }        // Optional
        public int Timeout { get; }        // Optional, default 30s

        // Private constructor, only accessible by the Builder
        private HttpRequest(Builder builder)
        {
            Url = builder.Url;
            Method = builder.Method;
            Headers = new Dictionary<string, string>(builder.Headers); // Defensive copy
            QueryParams = new Dictionary<string, string>(builder.QueryParams); // Defensive copy
            Body = builder.Body;
            Timeout = builder.Timeout;
        }

        public override string ToString()
        {
            return $"HttpRequest{{" +
                   $"url='{Url}', " +
                   $"method='{Method}', " +
                   $"headers={{{string.Join(", ", Headers.Select(kv => $"{kv.Key}={kv.Value}"))}}}, " +
                   $"queryParams={{{string.Join(", ", QueryParams.Select(kv => $"{kv.Key}={kv.Value}"))}}}, " +
                   $"body='{(Body != null ? (Body.Length > 10 ? Body.Substring(0, 10) + "..." : Body) : "null")}', " +
                   $"timeout={Timeout}}}";
        }

        // --- Builder Class ---
        public class Builder
        {
            // Required parameter
            public string Url { get; }

            // Optional parameters - initialized to default values
            public string Method { get; private set; } = "GET";
            public Dictionary<string, string> Headers { get; } = new Dictionary<string, string>();
            public Dictionary<string, string> QueryParams { get; } = new Dictionary<string, string>();
            public string Body { get; private set; }
            public int Timeout { get; private set; } = 30000; // 30 seconds default

            // Builder constructor for required fields
            public Builder(string url)
            {
                if (string.IsNullOrWhiteSpace(url))
                {
                    throw new ArgumentException("URL cannot be null or empty.", nameof(url));
                }
                Url = url;
            }

            // Setter-like methods for optional fields, returning the Builder for fluency
            public Builder WithMethod(string method)
            {
                Method = string.IsNullOrWhiteSpace(method) ? "GET" : method.ToUpper();
                return this;
            }

            public Builder WithHeader(string key, string value)
            {
                if (!string.IsNullOrEmpty(key) && !string.IsNullOrEmpty(value))
                {
                    Headers[key] = value;
                }
                return this;
            }

            public Builder WithQueryParam(string key, string value)
            {
                if (!string.IsNullOrEmpty(key) && !string.IsNullOrEmpty(value))
                {
                    QueryParams[key] = value;
                }
                return this;
            }

            public Builder WithBody(string body)
            {
                Body = body;
                return this;
            }

            public Builder WithTimeout(int timeoutMillis)
            {
                if (timeoutMillis > 0)
                {
                    Timeout = timeoutMillis;
                }
                return this;
            }

            // The final build method that creates the HttpRequest object
            public HttpRequest Build()
            {
                // Optionally, add validation logic here before creating the object
                if ((Method == "POST" || Method == "PUT") && string.IsNullOrEmpty(Body))
                {
                    Console.WriteLine($"Warning: Building {Method} request without a body for URL: {Url}");
                }
                return new HttpRequest(this);
            }
        }
    }
} 