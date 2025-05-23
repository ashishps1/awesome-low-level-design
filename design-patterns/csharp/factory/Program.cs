using System;

namespace Factory
{
    class Program
    {
        static void Main(string[] args)
        {
            // Using the factory
            Console.WriteLine("=== Using Factory Pattern ===");
            var emailNotification = SimpleNotificationFactory.CreateNotification("EMAIL");
            emailNotification.Send("Hello via Email!");

            var smsNotification = SimpleNotificationFactory.CreateNotification("SMS");
            smsNotification.Send("Hello via SMS!");

            var pushNotification = SimpleNotificationFactory.CreateNotification("PUSH");
            pushNotification.Send("Hello via Push!");

            // Using the naive approach
            Console.WriteLine("\n=== Using Naive Approach ===");
            var notificationService = new NotificationServiceNaive();
            notificationService.SendNotification("EMAIL", "Hello via Email!");
            notificationService.SendNotification("SMS", "Hello via SMS!");
            notificationService.SendNotification("PUSH", "Hello via Push!");
        }
    }
} 