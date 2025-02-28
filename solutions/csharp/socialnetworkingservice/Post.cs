using System;
using System.Collections.Generic;

namespace SocialNetworkingService
{
    public class Post
    {
        public string Id { get; }
        public string UserId { get; }
        public string Content { get; }
        public List<string> ImageUrls { get; }
        public List<string> VideoUrls { get; }
        public DateTime Timestamp { get; }
        public List<string> Likes { get; }
        public List<Comment> Comments { get; }

        public Post(string id, string userId, string content, List<string> imageUrls, List<string> videoUrls, DateTime timestamp, List<string> likes, List<Comment> comments)
        {
            Id = id;
            UserId = userId;
            Content = content;
            ImageUrls = imageUrls;
            VideoUrls = videoUrls;
            Timestamp = timestamp;
            Likes = likes;
            Comments = comments;
        }
    }
}