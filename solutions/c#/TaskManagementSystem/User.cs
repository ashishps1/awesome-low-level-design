namespace TaskManagementSystem
{
    public class User
    {
        public string Id { get; }
        public string Name { get; }
        public string Email { get; }

        public User(string id, string name, string email)
        {
            Id = id;
            Name = name;
            Email = email;
        }

        public override bool Equals(object obj)
        {
            if (obj is User user)
            {
                return Id == user.Id;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }
    }
}