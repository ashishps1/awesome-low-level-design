using System;

namespace PubSubSystem
{
    public class PubSubSystemDemo
    {
        public static void Run()
        {
            // Create topics
            var topic1 = new Topic("Topic1");
            var topic2 = new Topic("Topic2");

            // Create publishers
            var publisher1 = new Publisher();
            var publisher2 = new Publisher();

            // Create subscribers
            var subscriber1 = new PrintSubscriber("Subscriber1");
            var subscriber2 = new PrintSubscriber("Subscriber2");
            var subscriber3 = new PrintSubscriber("Subscriber3");

            publisher1.RegisterTopic(topic1);
            publisher2.RegisterTopic(topic2);

            // Subscribe to topics
            topic1.AddSubscriber(subscriber1);
            topic1.AddSubscriber(subscriber2);
            topic2.AddSubscriber(subscriber2);
            topic2.AddSubscriber(subscriber3);

            // Publish messages
            publisher1.Publish(topic1, new Message("Message1 for Topic1"));
            publisher1.Publish(topic1, new Message("Message2 for Topic1"));
            publisher2.Publish(topic2, new Message("Message1 for Topic2"));

            // Unsubscribe from a topic
            topic1.RemoveSubscriber(subscriber2);

            // Publish more messages
            publisher1.Publish(topic1, new Message("Message3 for Topic1"));
            publisher2.Publish(topic2, new Message("Message2 for Topic2"));
        }
    }
}