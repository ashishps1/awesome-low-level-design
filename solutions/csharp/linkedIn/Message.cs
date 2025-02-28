using System;

namespace LinkedInNamespace
{
    public class Message
    {
        public string Id { get; }
        public User Sender { get; }
        public User Receiver { get; }
        public string Content { get; }
        public DateTime Timestamp { get; }

        public Message(string id, User sender, User receiver, string content, DateTime timestamp)
        {
            Id = id;
            Sender = sender;
            Receiver = receiver;
            Content = content;
            Timestamp = timestamp;
        }
    }
}