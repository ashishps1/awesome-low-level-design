class RecommendationService
{
    private RecommendationStrategy strategy;

    public RecommendationService(RecommendationStrategy strategy)
    {
        this.strategy = strategy;
    }

    public void SetStrategy(RecommendationStrategy strategy)
    {
        this.strategy = strategy;
    }

    public List<Song> GenerateRecommendations(List<Song> allSongs)
    {
        return strategy.Recommend(allSongs);
    }
}