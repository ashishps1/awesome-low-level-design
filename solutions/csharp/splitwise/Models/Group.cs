class Group
{
    private readonly string id;
    private readonly string name;
    private readonly List<User> members;

    public Group(string name, List<User> members)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.members = members;
    }

    public string GetId() => id;
    public string GetName() => name;
    public List<User> GetMembers() => new List<User>(members);
}