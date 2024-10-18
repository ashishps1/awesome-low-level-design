namespace OnlineStockBrokerageSystem
{
    public class User
    {
        public string UserId { get; }
        public string Name { get; }
        public string Email { get; }

        public User(string userId, string name, string email)
        {
            UserId = userId;
            Name = name;
            Email = email;
        }
    }
}