class Post : Subject
{
    private readonly string id;
    private readonly Member author;
    private readonly string content;
    private readonly DateTime createdAt;
    private readonly List<Like> likes = new List<Like>();
    private readonly List<Comment> comments = new List<Comment>();

    public Post(Member author, string content)
    {
        this.id = Guid.NewGuid().ToString();
        this.author = author;
        this.content = content;
        this.createdAt = DateTime.Now;
        AddObserver(author);
    }

    public void AddLike(Member member)
    {
        likes.Add(new Like(member));
        string notificationContent = $"{member.GetName()} liked your post.";
        var notification = new Notification(author.GetId(), NotificationType.POST_LIKE, notificationContent);
        NotifyObservers(notification);
    }

    public void AddComment(Member member, string text)
    {
        comments.Add(new Comment(member, text));
        string notificationContent = $"{member.GetName()} commented on your post: \"{text}\"";
        var notification = new Notification(author.GetId(), NotificationType.POST_COMMENT, notificationContent);
        NotifyObservers(notification);
    }

    public string GetId() { return id; }
    public Member GetAuthor() { return author; }
    public string GetContent() { return content; }
    public DateTime GetCreatedAt() { return createdAt; }
    public List<Like> GetLikes() { return likes; }
    public List<Comment> GetComments() { return comments; }
}