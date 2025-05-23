using System;

namespace ChainOfResponsibility
{
    public class AuthorizationHandler : BaseHandler
    {
        public override void Handle(Request request)
        {
            if (string.IsNullOrEmpty(request.UserRole) || request.UserRole != "ADMIN")
            {
                Console.WriteLine($"AuthorizationHandler: User {request.User} is not authorized");
                return;
            }

            Console.WriteLine($"AuthorizationHandler: User {request.User} is authorized");
            HandleNext(request);
        }
    }
} 