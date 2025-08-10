abstract class User : IOrderObserver
{
    protected readonly string id;
    protected readonly string name;
    protected readonly string phone;

    public User(string name, string phone)
    {
        this.id = Guid.NewGuid().ToString();
        this.name = name;
        this.phone = phone;
    }

    public string GetId() { return id; }
    public string GetName() { return name; }

    public abstract void OnUpdate(Order order);
}