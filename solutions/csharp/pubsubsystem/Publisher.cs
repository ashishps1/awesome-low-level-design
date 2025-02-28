using System;
using System.Collections.Generic;

namespace PubSubSystem
{
    public class Publisher
    {
        private readonly HashSet<Topic> _topics;

        public Publisher()
        {
            _topics = new HashSet<Topic>();
        }

        public void RegisterTopic(Topic topic)
        {
            _topics.Add(topic);
        }

        public void Publish(Topic topic, Message message)
        {
            if (!_topics.Contains(topic))
            {
                Console.WriteLine($"This publisher can't publish to topic: {topic.Name}");
                return;
            }

            topic.Publish(message);
        }
    }
}