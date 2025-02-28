using System;

namespace LinkedInNamespace
{
    public class Notification
    {
        public string Id { get; }
        public User User { get; }
        public NotificationType Type { get; }
        public string Content { get; }
        public DateTime Timestamp { get; }

        public Notification(string id, User user, NotificationType type, string content, DateTime timestamp)
        {
            Id = id;
            User = user;
            Type = type;
            Content = content;
            Timestamp = timestamp;
        }
    }
}