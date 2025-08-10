using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

public class PubSubDemo
{
    public static void Main(string[] args)
    {
        PubSubService pubSubService = PubSubService.GetInstance();

        // --- Create Subscribers ---
        ISubscriber sportsFan1 = new NewsSubscriber("SportsFan1");
        ISubscriber sportsFan2 = new NewsSubscriber("SportsFan2");
        ISubscriber techie1 = new NewsSubscriber("Techie1");
        ISubscriber allNewsReader = new NewsSubscriber("AllNewsReader");
        ISubscriber systemAdmin = new AlertSubscriber("SystemAdmin");

        // --- Create Topics and Subscriptions ---
        const string SPORTS_TOPIC = "SPORTS";
        const string TECH_TOPIC = "TECH";
        const string WEATHER_TOPIC = "WEATHER";

        pubSubService.CreateTopic(SPORTS_TOPIC);
        pubSubService.CreateTopic(TECH_TOPIC);
        pubSubService.CreateTopic(WEATHER_TOPIC);

        pubSubService.Subscribe(SPORTS_TOPIC, sportsFan1);
        pubSubService.Subscribe(SPORTS_TOPIC, sportsFan2);
        pubSubService.Subscribe(SPORTS_TOPIC, allNewsReader);
        pubSubService.Subscribe(SPORTS_TOPIC, systemAdmin);

        pubSubService.Subscribe(TECH_TOPIC, techie1);
        pubSubService.Subscribe(TECH_TOPIC, allNewsReader);

        Console.WriteLine("\n--- Publishing Messages ---");

        // --- Publish to SPORTS topic ---
        pubSubService.Publish(SPORTS_TOPIC, new Message("Team A wins the championship!"));
        // Expected: SportsFan1, SportsFan2, AllNewsReader, SystemAdmin receive this.

        // --- Publish to TECH topic ---
        pubSubService.Publish(TECH_TOPIC, new Message("New AI model released."));
        // Expected: Techie1, AllNewsReader receive this.

        // --- Publish to WEATHER topic (no subscribers) ---
        pubSubService.Publish(WEATHER_TOPIC, new Message("Sunny with a high of 75°F."));
        // Expected: Message is dropped.

        // Allow some time for async messages to be processed
        Thread.Sleep(500);

        Console.WriteLine("\n--- Unsubscribing a user and re-publishing ---");

        // SportsFan2 gets tired of sports news
        pubSubService.Unsubscribe(SPORTS_TOPIC, sportsFan2);

        // Publish another message to SPORTS
        pubSubService.Publish(SPORTS_TOPIC, new Message("Major player traded to Team B."));
        // Expected: SportsFan1, AllNewsReader, SystemAdmin receive this. SportsFan2 does NOT.

        // Give messages time to be delivered
        Thread.Sleep(500);

        // --- Shutdown the service ---
        pubSubService.Shutdown();
    }
}