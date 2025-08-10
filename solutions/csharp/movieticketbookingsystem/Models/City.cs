class City
{
    private readonly string id;
    private readonly string name;

    public City(string id, string name)
    {
        this.id = id;
        this.name = name;
    }

    public string GetId() { return id; }
    public string GetName() { return name; }
}