using System;

namespace PubSubSystem
{
    public class PrintSubscriber : ISubscriber
    {
        public string Name { get; }

        public PrintSubscriber(string name)
        {
            Name = name;
        }

        public void OnMessage(Message message)
        {
            Console.WriteLine($"Subscriber {Name} received message: {message.Content}");
        }
    }
}