class Tag : IComparable<Tag>
{
    private readonly string name;

    public Tag(string name)
    {
        this.name = name;
    }

    public string GetName() { return name; }

    public int CompareTo(Tag other)
    {
        return string.Compare(name, other.name, StringComparison.Ordinal);
    }

    public override bool Equals(object obj)
    {
        if (obj is Tag other)
        {
            return name.Equals(other.name, StringComparison.OrdinalIgnoreCase);
        }
        return false;
    }

    public override int GetHashCode()
    {
        return name.ToLower().GetHashCode();
    }
}