using System.Collections.Concurrent;

namespace Splitwise
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }
        public ConcurrentDictionary<string, double> Balances { get; }

        public User(string id, string name, string email)
        {
            Id = id;
            Name = name;
            Email = email;
            Balances = new ConcurrentDictionary<string, double>();
        }
    }
}