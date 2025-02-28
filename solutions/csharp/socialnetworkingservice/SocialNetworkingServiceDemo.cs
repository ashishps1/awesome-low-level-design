using System;
using System.Collections.Generic;

namespace SocialNetworkingService
{
    public class SocialNetworkingServiceDemo
    {
        public static void Run()
        {
            var socialNetworkingService = SocialNetworkingService.GetInstance();

            // User registration
            var user1 = new User("1", "John Doe", "john@example.com", "password", "profile1.jpg", "I love coding!", new List<string>(), new List<Post>());
            var user2 = new User("2", "Jane Smith", "jane@example.com", "password", "profile2.jpg", "Exploring the world!", new List<string>(), new List<Post>());
            socialNetworkingService.RegisterUser(user1);
            socialNetworkingService.RegisterUser(user2);

            // User login
            var loggedInUser = socialNetworkingService.LoginUser("john@example.com", "password");
            if (loggedInUser != null)
            {
                Console.WriteLine("User logged in: " + loggedInUser.Name);
            }
            else
            {
                Console.WriteLine("Invalid email or password.");
            }

            // Send friend request
            socialNetworkingService.SendFriendRequest(user1.Id, user2.Id);

            // Accept friend request
            socialNetworkingService.AcceptFriendRequest(user2.Id, user1.Id);

            // Create posts
            var post1 = new Post("post1", user1.Id, "My first post!", new List<string>(), new List<string>(), DateTime.Now, new List<string>(), new List<Comment>());
            var post2 = new Post("post2", user2.Id, "Having a great day!", new List<string>(), new List<string>(), DateTime.Now, new List<string>(), new List<Comment>());
            socialNetworkingService.CreatePost(post1);
            socialNetworkingService.CreatePost(post2);

            // Like a post
            socialNetworkingService.LikePost(user2.Id, post1.Id);

            // Comment on a post
            var comment = new Comment("comment1", user2.Id, post1.Id, "Great post!", DateTime.Now);
            socialNetworkingService.CommentOnPost(comment);

            // Get newsfeed
            var newsfeed = socialNetworkingService.GetNewsfeed(user1.Id);
            Console.WriteLine("Newsfeed:");
            foreach (var post in newsfeed)
            {
                Console.WriteLine("Post: " + post.Content);
                Console.WriteLine("Likes: " + post.Likes.Count);
                Console.WriteLine("Comments: " + post.Comments.Count);
                Console.WriteLine();
            }

            // Get notifications
            var notifications = socialNetworkingService.GetNotifications(user1.Id);
            Console.WriteLine("Notifications:");
            foreach (var notification in notifications)
            {
                Console.WriteLine("Type: " + notification.Type);
                Console.WriteLine("Content: " + notification.Content);
                Console.WriteLine();
            }
        }
    }
}