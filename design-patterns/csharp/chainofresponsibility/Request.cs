namespace ChainOfResponsibility
{
    public class Request
    {
        public string User { get; }
        public string UserRole { get; }
        public int RequestCount { get; }
        public string Payload { get; }

        public Request(string user, string role, int requestCount, string payload)
        {
            User = user;
            UserRole = role;
            RequestCount = requestCount;
            Payload = payload;
        }
    }
} 