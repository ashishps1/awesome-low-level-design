class User
{
    private readonly string id;
    private readonly string name;
    private int reputation;
    private readonly object reputationLock = new object();

    public User(string name)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.reputation = 0;
    }

    public void UpdateReputation(int change)
    {
        lock (reputationLock)
        {
            reputation += change;
        }
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
    public int GetReputation() 
    { 
        lock (reputationLock)
        {
            return reputation;
        }
    }
}