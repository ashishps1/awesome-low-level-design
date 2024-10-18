using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;

namespace SocialNetworkingService
{
    public class SocialNetworkingService
    {
        private static SocialNetworkingService _instance;
        private readonly ConcurrentDictionary<string, User> _users;
        private readonly ConcurrentDictionary<string, Post> _posts;
        private readonly ConcurrentDictionary<string, List<Notification>> _notifications;

        private SocialNetworkingService()
        {
            _users = new ConcurrentDictionary<string, User>();
            _posts = new ConcurrentDictionary<string, Post>();
            _notifications = new ConcurrentDictionary<string, List<Notification>>();
        }

        public static SocialNetworkingService GetInstance()
        {
            if (_instance == null)
            {
                _instance = new SocialNetworkingService();
            }
            return _instance;
        }

        public void RegisterUser(User user)
        {
            _users[user.Id] = user;
        }

        public User LoginUser(string email, string password)
        {
            return _users.Values.FirstOrDefault(user => user.Email == email && user.Password == password);
        }

        public void SendFriendRequest(string senderId, string receiverId)
        {
            if (_users.TryGetValue(receiverId, out var receiver))
            {
                var notification = new Notification(GenerateNotificationId(), receiverId, NotificationType.FRIEND_REQUEST, "Friend request from " + senderId, DateTime.Now);
                AddNotification(receiverId, notification);
            }
        }

        public void AcceptFriendRequest(string userId, string friendId)
        {
            if (_users.TryGetValue(userId, out var user) && _users.TryGetValue(friendId, out var friend))
            {
                user.Friends.Add(friendId);
                friend.Friends.Add(userId);
                var notification = new Notification(GenerateNotificationId(), friendId, NotificationType.FRIEND_REQUEST_ACCEPTED, "Friend request accepted by " + userId, DateTime.Now);
                AddNotification(friendId, notification);
            }
        }

        public void CreatePost(Post post)
        {
            _posts[post.Id] = post;
            if (_users.TryGetValue(post.UserId, out var user))
            {
                user.Posts.Add(post);
            }
        }

        public List<Post> GetNewsfeed(string userId)
        {
            var newsfeed = new List<Post>();
            if (_users.TryGetValue(userId, out var user))
            {
                foreach (var friendId in user.Friends)
                {
                    if (_users.TryGetValue(friendId, out var friend))
                    {
                        newsfeed.AddRange(friend.Posts);
                    }
                }
                newsfeed.AddRange(user.Posts);
                newsfeed.Sort((p1, p2) => p2.Timestamp.CompareTo(p1.Timestamp));
            }
            return newsfeed;
        }

        public void LikePost(string userId, string postId)
        {
            if (_posts.TryGetValue(postId, out var post) && !post.Likes.Contains(userId))
            {
                post.Likes.Add(userId);
                var notification = new Notification(GenerateNotificationId(), post.UserId, NotificationType.LIKE, "Your post was liked by " + userId, DateTime.Now);
                AddNotification(post.UserId, notification);
            }
        }

        public void CommentOnPost(Comment comment)
        {
            if (_posts.TryGetValue(comment.PostId, out var post))
            {
                post.Comments.Add(comment);
                var notification = new Notification(GenerateNotificationId(), post.UserId, NotificationType.COMMENT, "Your post received a comment from " + comment.UserId, DateTime.Now);
                AddNotification(post.UserId, notification);
            }
        }

        private void AddNotification(string userId, Notification notification)
        {
            _notifications.AddOrUpdate(userId, new List<Notification> { notification }, (key, list) =>
            {
                list.Add(notification);
                return list;
            });
        }

        public List<Notification> GetNotifications(string userId)
        {
            return _notifications.TryGetValue(userId, out var userNotifications) ? userNotifications : new List<Notification>();
        }

        private string GenerateNotificationId()
        {
            return Guid.NewGuid().ToString();
        }
    }
}