using System;

namespace ChainOfResponsibility
{
    public class BusinessLogicHandler : BaseHandler
    {
        public override void Handle(Request request)
        {
            Console.WriteLine($"BusinessLogicHandler: Processing request for user {request.User}");
            HandleNext(request);
        }
    }
} 