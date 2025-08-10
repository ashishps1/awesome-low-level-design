class PostService
{
    private readonly PostRepository postRepository = PostRepository.GetInstance();
    private readonly List<IPostObserver> observers = new List<IPostObserver>();

    public void AddObserver(IPostObserver observer)
    {
        observers.Add(observer);
    }

    public Post CreatePost(User author, string content)
    {
        Post post = new Post(author, content);
        postRepository.Save(post);
        author.AddPost(post);
        foreach (var observer in observers)
        {
            observer.OnPostCreated(post);
        }
        return post;
    }

    public void LikePost(User user, string postId)
    {
        Post post = postRepository.FindById(postId);
        post.AddLike(user);
        foreach (var observer in observers)
        {
            observer.OnLike(post, user);
        }
    }

    public void AddComment(User author, string commentableId, string content)
    {
        Comment comment = new Comment(author, content);
        Post post = postRepository.FindById(commentableId);
        post.AddComment(comment);
        foreach (var observer in observers)
        {
            observer.OnComment(post, comment);
        }
    }
}