class Tag
{
    private readonly string name;

    public Tag(string name)
    {
        this.name = name;
    }

    public string GetName() => name;
}