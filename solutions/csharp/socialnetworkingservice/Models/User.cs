class User
{
    private readonly string id;
    private readonly string name;
    private readonly string email;
    private readonly HashSet<User> friends = new HashSet<User>();
    private readonly List<Post> posts = new List<Post>();

    public User(string name, string email)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.email = email;
    }

    public void AddFriend(User friend)
    {
        friends.Add(friend);
    }

    public void AddPost(Post post)
    {
        posts.Add(post);
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public HashSet<User> GetFriends() { return friends; }
    public List<Post> GetPosts() { return posts; }
}