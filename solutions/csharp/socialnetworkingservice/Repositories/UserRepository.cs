class UserRepository
{
    private static readonly UserRepository INSTANCE = new UserRepository();
    private readonly Dictionary<string, User> users = new Dictionary<string, User>();

    private UserRepository() { }

    public static UserRepository GetInstance()
    {
        return INSTANCE;
    }

    public void Save(User user)
    {
        users[user.GetId()] = user;
    }

    public User FindById(string id)
    {
        users.TryGetValue(id, out User user);
        return user;
    }
}