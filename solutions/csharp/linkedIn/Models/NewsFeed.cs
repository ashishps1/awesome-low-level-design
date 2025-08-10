class NewsFeed
{
    private readonly List<Post> posts;

    public NewsFeed(List<Post> posts)
    {
        this.posts = posts;
    }

    public void Display(IFeedSortingStrategy strategy)
    {
        var sortedPosts = strategy.Sort(posts);
        if (!sortedPosts.Any())
        {
            Console.WriteLine("  Your news feed is empty.");
            return;
        }

        foreach (var post in sortedPosts)
        {
            Console.WriteLine("----------------------------------------");
            Console.WriteLine($"Post by: {post.GetAuthor().GetName()} (at {post.GetCreatedAt().ToShortDateString()})");
            Console.WriteLine($"Content: {post.GetContent()}");
            Console.WriteLine($"Likes: {post.GetLikes().Count}, Comments: {post.GetComments().Count}");
            Console.WriteLine("----------------------------------------");
        }
    }
}