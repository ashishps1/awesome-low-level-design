class ChronologicalStrategy : INewsFeedGenerationStrategy
{
    public List<Post> GenerateFeed(User user)
    {
        HashSet<User> friends = user.GetFriends();
        List<Post> feed = new List<Post>();

        foreach (User friend in friends)
        {
            feed.AddRange(friend.GetPosts());
        }

        // Sort posts by timestamp in reverse (most recent first)
        feed.Sort((p1, p2) => p2.GetTimestamp().CompareTo(p1.GetTimestamp()));

        return feed;
    }
}