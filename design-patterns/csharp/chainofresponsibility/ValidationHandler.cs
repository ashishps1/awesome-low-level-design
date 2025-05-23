using System;

namespace ChainOfResponsibility
{
    public class ValidationHandler : BaseHandler
    {
        public override void Handle(Request request)
        {
            if (string.IsNullOrEmpty(request.Payload))
            {
                Console.WriteLine("ValidationHandler: Request payload is empty");
                return;
            }

            Console.WriteLine("ValidationHandler: Request payload is valid");
            HandleNext(request);
        }
    }
} 