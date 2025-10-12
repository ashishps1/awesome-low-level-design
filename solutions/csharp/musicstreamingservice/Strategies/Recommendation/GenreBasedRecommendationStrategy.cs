class GenreBasedRecommendationStrategy : RecommendationStrategy
{
    public override List<Song> Recommend(List<Song> allSongs)
    {
        Console.WriteLine("Generating genre-based recommendations (simulated)...");
        var shuffled = new List<Song>(allSongs);
        var random = new Random();
        for (int i = shuffled.Count - 1; i > 0; i--)
        {
            int j = random.Next(i + 1);
            var temp = shuffled[i];
            shuffled[i] = shuffled[j];
            shuffled[j] = temp;
        }
        return shuffled.Take(Math.Min(5, shuffled.Count)).ToList();
    }
}