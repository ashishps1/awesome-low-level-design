using System;

namespace ChainOfResponsibility
{
    public class AuthHandler : BaseHandler
    {
        public override void Handle(Request request)
        {
            if (string.IsNullOrEmpty(request.User))
            {
                Console.WriteLine("AuthHandler: User is not authenticated");
                return;
            }

            Console.WriteLine($"AuthHandler: User {request.User} is authenticated");
            HandleNext(request);
        }
    }
} 