class TagSearchStrategy : ISearchStrategy
{
    private readonly Tag tag;

    public TagSearchStrategy(Tag tag)
    {
        this.tag = tag;
    }

    public List<Question> Filter(List<Question> questions)
    {
        return questions
            .Where(q => q.GetTags().Any(t => t.GetName().Equals(tag.GetName(), StringComparison.OrdinalIgnoreCase)))
            .ToList();
    }
}