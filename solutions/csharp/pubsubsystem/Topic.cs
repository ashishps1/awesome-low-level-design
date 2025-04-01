using System.Collections.Concurrent;
using System.Collections.Generic;

namespace PubSubSystem
{
    public class Topic
    {
        public string Name { get; }
        private readonly ConcurrentBag<ISubscriber> _subscribers;

        public Topic(string name)
        {
            Name = name;
            _subscribers = new ConcurrentBag<ISubscriber>();
        }

        public void AddSubscriber(ISubscriber subscriber)
        {
            _subscribers.Add(subscriber);
        }

        public void RemoveSubscriber(ISubscriber subscriber)
        {
            _subscribers.TryTake(out subscriber);
        }

        public void Publish(Message message)
        {
            foreach (var subscriber in _subscribers)
            {
                subscriber.OnMessage(message);
            }
        }
    }
}