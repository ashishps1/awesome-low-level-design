class UserSearchStrategy : ISearchStrategy
{
    private readonly User user;

    public UserSearchStrategy(User user)
    {
        this.user = user;
    }

    public List<Question> Filter(List<Question> questions)
    {
        return questions
            .Where(q => q.GetAuthor().GetId().Equals(user.GetId()))
            .ToList();
    }
}