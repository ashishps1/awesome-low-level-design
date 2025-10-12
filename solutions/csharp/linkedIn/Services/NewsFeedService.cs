class NewsFeedService
{
    private readonly Dictionary<string, List<Post>> allPosts = new Dictionary<string, List<Post>>();
    private readonly object lockObj = new object();

    public void AddPost(Member member, Post post)
    {
        lock (lockObj)
        {
            if (!allPosts.ContainsKey(member.GetId()))
            {
                allPosts[member.GetId()] = new List<Post>();
            }
            allPosts[member.GetId()].Add(post);
        }
    }

    public List<Post> GetMemberPosts(Member member)
    {
        lock (lockObj)
        {
            return allPosts.TryGetValue(member.GetId(), out var posts) ? posts : new List<Post>();
        }
    }

    public void DisplayFeedForMember(Member member, IFeedSortingStrategy feedSortingStrategy)
    {
        var feedPosts = new List<Post>();

        foreach (var connection in member.GetConnections())
        {
            var connectionPosts = GetMemberPosts(connection);
            feedPosts.AddRange(connectionPosts);
        }

        var feed = new NewsFeed(feedPosts);
        feed.Display(feedSortingStrategy);
    }
}