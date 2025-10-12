interface INewsFeedGenerationStrategy
{
    List<Post> GenerateFeed(User user);
}