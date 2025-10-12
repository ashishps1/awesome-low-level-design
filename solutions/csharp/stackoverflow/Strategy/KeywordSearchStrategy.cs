class KeywordSearchStrategy : ISearchStrategy
{
    private readonly string keyword;

    public KeywordSearchStrategy(string keyword)
    {
        this.keyword = keyword.ToLower();
    }

    public List<Question> Filter(List<Question> questions)
    {
        return questions
            .Where(q => q.GetTitle().ToLower().Contains(keyword) || q.GetBody().ToLower().Contains(keyword))
            .ToList();
    }
}