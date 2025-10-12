class PostRepository
{
    private static readonly PostRepository INSTANCE = new PostRepository();
    private readonly Dictionary<string, Post> posts = new Dictionary<string, Post>();

    private PostRepository() { }

    public static PostRepository GetInstance()
    {
        return INSTANCE;
    }

    public void Save(Post post)
    {
        posts[post.GetId()] = post;
    }

    public Post FindById(string id)
    {
        posts.TryGetValue(id, out Post post);
        return post;
    }
}