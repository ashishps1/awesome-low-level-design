abstract class CommentableEntity
{
    protected readonly string id;
    protected readonly User author;
    protected readonly string content;
    protected readonly DateTime timestamp;
    private readonly HashSet<User> likes = new HashSet<User>();
    protected readonly List<Comment> comments = new List<Comment>();

    public CommentableEntity(User author, string content)
    {
        this.id = Guid.NewGuid().ToString();
        this.author = author;
        this.content = content;
        this.timestamp = DateTime.Now;
    }

    public void AddLike(User user)
    {
        likes.Add(user);
    }

    public void AddComment(Comment comment)
    {
        comments.Add(comment);
    }

    public string GetId() { return id; }
    public User GetAuthor() { return author; }
    public string GetContent() { return content; }
    public DateTime GetTimestamp() { return timestamp; }
    public List<Comment> GetComments() { return comments; }
    public HashSet<User> GetLikes() { return likes; }
}