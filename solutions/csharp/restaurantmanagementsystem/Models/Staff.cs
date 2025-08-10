abstract class Staff
{
    protected string id;
    protected string name;

    public Staff(string id, string name)
    {
        this.id = id;
        this.name = name;
    }

    public string GetId() => id;
    public string GetName() => name;
}