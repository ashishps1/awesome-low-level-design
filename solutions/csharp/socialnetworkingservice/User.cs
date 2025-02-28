using System.Collections.Generic;

namespace SocialNetworkingService
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string Password { get; }
        public string ProfilePicture { get; }
        public string Bio { get; }
        public List<string> Friends { get; }
        public List<Post> Posts { get; }

        public User(string id, string name, string email, string password, string profilePicture, string bio, List<string> friends, List<Post> posts)
        {
            Id = id;
            Name = name;
            Email = email;
            Password = password;
            ProfilePicture = profilePicture;
            Bio = bio;
            Friends = friends;
            Posts = posts;
        }
    }
}