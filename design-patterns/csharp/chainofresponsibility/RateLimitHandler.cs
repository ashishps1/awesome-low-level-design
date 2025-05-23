using System;

namespace ChainOfResponsibility
{
    public class RateLimitHandler : BaseHandler
    {
        private const int MAX_REQUESTS = 5;

        public override void Handle(Request request)
        {
            if (request.RequestCount > MAX_REQUESTS)
            {
                Console.WriteLine($"RateLimitHandler: User {request.User} has exceeded the rate limit");
                return;
            }

            Console.WriteLine($"RateLimitHandler: User {request.User} is within rate limit");
            HandleNext(request);
        }
    }
} 