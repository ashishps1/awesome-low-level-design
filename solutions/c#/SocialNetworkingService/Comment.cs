using System;

namespace SocialNetworkingService
{
    public class Comment
    {
        public string Id { get; }
        public string UserId { get; }
        public string PostId { get; }
        public string Content { get; }
        public DateTime Timestamp { get; }

        public Comment(string id, string userId, string postId, string content, DateTime timestamp)
        {
            Id = id;
            UserId = userId;
            PostId = postId;
            Content = content;
            Timestamp = timestamp;
        }
    }
}