class Comment
{
    private readonly string id;
    private readonly string content;
    private readonly User author;
    private readonly DateTime timestamp;

    public Comment(string content, User author)
    {
        this.id = Guid.NewGuid().ToString();
        this.content = content;
        this.author = author;
        this.timestamp = DateTime.Now;
    }

    public User GetAuthor() => author;
}