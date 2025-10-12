class SocialNetworkFacade
{
    private readonly UserService userService;
    private readonly PostService postService;
    private readonly NewsFeedService newsFeedService;

    public SocialNetworkFacade()
    {
        this.userService = new UserService();
        this.postService = new PostService();
        this.newsFeedService = new NewsFeedService();
        // Wire up the observer
        postService.AddObserver(new UserNotifier());
    }

    public User CreateUser(string name, string email)
    {
        return userService.CreateUser(name, email);
    }

    public void AddFriend(string userId1, string userId2)
    {
        userService.AddFriend(userId1, userId2);
    }

    public Post CreatePost(string authorId, string content)
    {
        User author = userService.GetUserById(authorId);
        return postService.CreatePost(author, content);
    }

    public void AddComment(string userId, string postId, string content)
    {
        User user = userService.GetUserById(userId);
        postService.AddComment(user, postId, content);
    }

    public void LikePost(string userId, string postId)
    {
        User user = userService.GetUserById(userId);
        postService.LikePost(user, postId);
    }

    public List<Post> GetNewsFeed(string userId)
    {
        User user = userService.GetUserById(userId);
        return newsFeedService.GetNewsFeed(user);
    }
}