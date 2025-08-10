class ChronologicalSortStrategy : IFeedSortingStrategy
{
    public List<Post> Sort(List<Post> posts)
    {
        return posts.OrderByDescending(post => post.GetCreatedAt()).ToList();
    }
}