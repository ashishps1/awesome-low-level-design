using System.Collections.Generic;

namespace LinkedInNamespace
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public string Password { get; }
        public Profile Profile { get; set; }
        public List<Connection> Connections { get; }
        public List<Message> Inbox { get; }
        public List<Message> SentMessages { get; }

        public User(string id, string name, string email, string password, Profile profile)
        {
            Id = id;
            Name = name;
            Email = email;
            Password = password;
            Profile = profile;
            Connections = new List<Connection>();
            Inbox = new List<Message>();
            SentMessages = new List<Message>();
        }
    }
}