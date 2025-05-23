using System;

namespace Factory
{
    public class NotificationServiceNaive
    {
        public void SendNotification(string type, string message)
        {
            if (type == "EMAIL")
            {
                var email = new EmailNotification();
                email.Send(message);
            }
            else if (type == "SMS")
            {
                var sms = new SMSNotification();
                sms.Send(message);
            }
            else if (type == "PUSH")
            {
                var push = new PushNotification();
                push.Send(message);
            }
        }
    }
} 