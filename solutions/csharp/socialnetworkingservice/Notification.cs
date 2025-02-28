using System;

namespace SocialNetworkingService
{
    public class Notification
    {
        public string Id { get; }
        public string UserId { get; }
        public NotificationType Type { get; }
        public string Content { get; }
        public DateTime Timestamp { get; }

        public Notification(string id, string userId, NotificationType type, string content, DateTime timestamp)
        {
            Id = id;
            UserId = userId;
            Type = type;
            Content = content;
            Timestamp = timestamp;
        }
    }
}