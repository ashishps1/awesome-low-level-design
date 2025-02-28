namespace OnlineAuctionSystem
{
    public class User
    {
        public string Id { get; }
        public string Username { get; }
        public string Email { get; }

        public User(string id, string username, string email)
        {
            Id = id;
            Username = username;
            Email = email;
        }
    }
}