class SearchService
{
    private readonly ICollection<Member> members;

    public SearchService(ICollection<Member> members)
    {
        this.members = members;
    }

    public List<Member> SearchByName(string name)
    {
        return members
            .Where(member => member.GetName().ToLower().Contains(name.ToLower()))
            .ToList();
    }
}