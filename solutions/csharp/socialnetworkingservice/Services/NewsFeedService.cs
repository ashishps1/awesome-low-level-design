class NewsFeedService
{
    private INewsFeedGenerationStrategy strategy;

    public NewsFeedService()
    {
        this.strategy = new ChronologicalStrategy(); // Default strategy
    }

    public void SetStrategy(INewsFeedGenerationStrategy strategy)
    {
        this.strategy = strategy;
    }

    public List<Post> GetNewsFeed(User user)
    {
        return strategy.GenerateFeed(user);
    }
}