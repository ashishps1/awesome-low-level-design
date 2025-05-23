using System;

namespace Factory
{
    public class PushNotification : INotification
    {
        public void Send(string message)
        {
            Console.WriteLine($"Sending push notification: {message}");
        }
    }
} 